/**
 * @file autodriver.cpp
 *
 */
/*
 * Based on https://github.com/sparkfun/L6470-AutoDriver/tree/master/Libraries/Arduino
 */
/* Copyright (C) 2017-2023 by Arjan van Vught mailto:info@orangepi-dmx.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <cstddef>
#include <cstdint>
#include <cassert>

// It would propably be 10X easier to write a wrapper class for the SPI device first and then include it here,
// since the spidev interface is quite low level.
extern "C" {
    #include <linux/ioctl.h>
    #include <linux/types.h>
    #include <linux/spi/spidev.h>
}

#define SPI_DEVICE "/dev/spidev0.0"
// ^^ This is a place holder for now.

#include "hal_spi.h"
#include "hal_gpio.h"

#include "autodriver.h"

#include "l6470constants.h"

#include "debug.h"

static constexpr uint8_t BUSY_PIN_NOT_USED = 0xFF;

uint8_t AutoDriver::m_nNumBoards[2];

AutoDriver::AutoDriver(uint8_t nPosition, uint8_t nSpiChipSelect, uint8_t nResetPin, uint8_t nBusyPin) :
	m_nSpiChipSelect(nSpiChipSelect),
	m_nResetPin(nResetPin),
	m_nBusyPin(nBusyPin),
	m_nPosition(nPosition),
	m_bIsBusy(false)
{
	DEBUG_ENTRY
	DEBUG_PRINTF("nPosition=%d, nSpiChipSelect=%d\n", static_cast<int>(nPosition), static_cast<int>(nSpiChipSelect));

	m_nNumBoards[nSpiChipSelect]++;

	DEBUG_PRINTF("m_nNumBoards[%d]=%d", static_cast<int>(nSpiChipSelect), static_cast<int>(m_nNumBoards[nSpiChipSelect]));
	DEBUG_EXIT
}

AutoDriver::AutoDriver(uint8_t nPosition, uint8_t nSpiChipSelect, uint8_t nResetPin) :
	m_nSpiChipSelect(nSpiChipSelect),
	m_nResetPin(nResetPin),
	m_nBusyPin(BUSY_PIN_NOT_USED),
	m_nPosition(nPosition),
	m_bIsBusy(false)
{
	DEBUG_ENTRY
	DEBUG_PRINTF("nPosition=%d, nSpiChipSelect=%d\n", static_cast<int>(nPosition), static_cast<int>(nSpiChipSelect));

	m_nNumBoards[nSpiChipSelect]++;

	DEBUG_PRINTF("m_nNumBoards[%d]=%d", static_cast<int>(nSpiChipSelect), static_cast<int>(m_nNumBoards[nSpiChipSelect]));
	DEBUG_EXIT
}

AutoDriver::~AutoDriver() {
	hardHiZ();
	m_bIsBusy = false;
	m_nNumBoards[m_nSpiChipSelect]--;
}

int AutoDriver::busyCheck() {
	if (m_nBusyPin == BUSY_PIN_NOT_USED) {
		if (getParam(L6470_PARAM_STATUS) & L6470_STATUS_BUSY) {
			return 0;
		} else {
			return 1;
		}
	} else {
		if (!m_bIsBusy) {
			if (getParam(L6470_PARAM_STATUS) & L6470_STATUS_BUSY) {
				return 0;
			} else {
				m_bIsBusy = true;
				return 1;
			}
		}
		// By default, the BUSY pin is forced low when the device is performing a command
		if (FUNC_PREFIX(gpio_lev(m_nBusyPin)) == HIGH) {
			m_bIsBusy = false;
			return 0;
		} else {
			return 1;
		}
	}
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvla"
#pragma GCC diagnostic ignored "-Wstack-usage="	//FIXME Needed for compilation on GD32F (https://www.gd32-dmx.org)

// references:
// - https://github.com/milekium/spidev-lib

uint8_t AutoDriver::SPIXfer(uint8_t data) {
	DEBUG_ENTRY

	char dataPacket[m_nNumBoards[m_nSpiChipSelect]];

	for (uint32_t i = 0; i < m_nNumBoards[m_nSpiChipSelect]; i++) {
		dataPacket[i] = 0;
	}

	dataPacket[m_nPosition] = static_cast<char>(data);

	// TODO: Select the board using the CS pin, somehow.
	struct spi_ioc_transfer spimsg[1] = { 0 };

	// char rx_buf[sizeof(dataPacket)];

	spimsg[0].rx_buf = NULL;
	spimsg[0].tx_buf = (unsigned long)dataPacket; // NOTE: There is something with the m_nNumBoards, that we should look into.
	spimsg[0].len = sizeof(dataPacket);

	ioctl(m_iSpiFd, SPI_IOC_MESSAGE(1), spimsg);
	// NOTE:                        ^ This probably has something to do with the m_nNumBoards.

	// FUNC_PREFIX(spi_chipSelect(m_nSpiChipSelect)); // This may require reworking to accomodate new interface lib.
	// FUNC_PREFIX(spi_set_speed_hz(2000000));
	// FUNC_PREFIX(spi_setDataMode(SPI_MODE3));
	// FUNC_PREFIX(spi_transfern(dataPacket, m_nNumBoards[m_nSpiChipSelect]));

	// DEBUG_PRINTF("data=%x, dataPacket[%d]=%x", data, m_nPosition, dataPacket[m_nPosition]);



	DEBUG_EXIT
	return static_cast<uint8_t>(dataPacket[m_nPosition]);
}

#pragma GCC diagnostic pop

uint16_t AutoDriver::getNumBoards() {
	uint16_t n = 0;

	for (uint32_t i = 0; i < (sizeof(m_nNumBoards) / sizeof(m_nNumBoards[0])); i++) {
		n += m_nNumBoards[i];
	}

	return n;
}

uint8_t AutoDriver::getNumBoards(uint8_t cs) {
	if (cs < (sizeof(m_nNumBoards) / sizeof(m_nNumBoards[0]))) {
		return m_nNumBoards[cs];
	} else {
		return 0;
	}
}

bool AutoDriver::IsConnected() {
	DEBUG_ENTRY

	if (getParam(L6470_PARAM_CONFIG) == 0x2e88) {
		DEBUG_EXIT
		return true;
	}

	DEBUG_EXIT
	return false;
}
