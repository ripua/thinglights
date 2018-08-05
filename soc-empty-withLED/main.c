/***********************************************************************************************//**
 * \file   main.c
 * \brief  Silicon Labs Empty Example Project
 *
 * This example demonstrates the bare minimum needed for a Blue Gecko C application
 * that allows Over-the-Air Device Firmware Upgrading (OTA DFU). The application
 * starts advertising after boot and restarts advertising after a connection is closed.
 ***************************************************************************************************
 * <b> (C) Copyright 2016 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

/* Board headers */
#include "init_mcu.h"
#include "init_board.h"
#include "init_app.h"
#include "ble-configuration.h"
#include "board_features.h"

#include "thunderboard/util.h"
#include "thunderboard/board.h"
#include "thunderboard/icm20648.h"

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"

/* Libraries containing default Gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"
#include "em_timer.h"

/* Device initialization header */
#include "hal-config.h"

/***********************************************************************************************//**
 * @addtogroup Application
 * @{
 **************************************************************************************************/

/***********************************************************************************************//**
 * @addtogroup app
 * @{
 **************************************************************************************************/

#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 4
#endif
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];

// Gecko configuration parameters (see gecko_configuration.h)
static const gecko_configuration_t config = {
  .config_flags = 0,
  .sleep.flags = SLEEP_FLAGS_DEEP_SLEEP_ENABLE,
  .bluetooth.max_connections = MAX_CONNECTIONS,
  .bluetooth.heap = bluetooth_stack_heap,
  .bluetooth.heap_size = sizeof(bluetooth_stack_heap),
  .bluetooth.sleep_clock_accuracy = 100, // ppm
  .gattdb = &bg_gattdb_data,
  .ota.flags = 0,
  .ota.device_name_len = 3,
  .ota.device_name_ptr = "OTA",
#if (HAL_PA_ENABLE) && defined(FEATURE_PA_HIGH_POWER)
  .pa.config_enable = 1, // Enable high power PA
  .pa.input = GECKO_RADIO_PA_INPUT_VBAT, // Configure PA input to VBAT
#endif // (HAL_PA_ENABLE) && defined(FEATURE_PA_HIGH_POWER)
};

// Flag for indicating DFU Reset must be performed
uint8_t boot_to_dfu = 0;

// Timer value
uint16_t timer_counter = 0;

/**
 * @brief  Main function
 */
int main(void)
{
  // Initialize device
  initMcu();
  // Initialize board
  initBoard();

  /**************************************************************************/
  /* Module init                                                            */
  /**************************************************************************/
  UTIL_init();
  BOARD_init();

  // Initialize application
  initApp();

  accelerometerSetThreshold();
  //ledToggle();
  //startTimerCounter();

  // Initialize stack
  gecko_init(&config);

  uint8_t r, g, b;
  uint8_t m;
  uint8_t statusCode;
  uint8_t enableMask;

  m = 0xFF;
  r = 0xFF;
  g = 0xFF;
  b = 0xFF;

  enableMask = m & 0xF;

  BOARD_rgbledEnable(true, enableMask);
  BOARD_rgbledSetColor(r, g, b);

  while (1) {
    /* Event pointer for handling events */
    struct gecko_cmd_packet* evt;

    /* Check for stack event. */
    evt = gecko_wait_event();

    /* Handle events */
    switch (BGLIB_MSG_ID(evt->header)) {
      /* This boot event is generated when the system boots up after reset.
       * Do not call any stack commands before receiving the boot event.
       * Here the system is set to start advertising immediately after boot procedure. */
      case gecko_evt_system_boot_id:

        /* Set advertising parameters. 100ms advertisement interval.
         * The first parameter is advertising set handle
         * The next two parameters are minimum and maximum advertising interval, both in
         * units of (milliseconds * 1.6).
         * The last two parameters are duration and maxevents left as default. */
        gecko_cmd_le_gap_set_advertise_timing(0, 160, 160, 0, 0);

        /* Start general advertising and enable connections. */
        gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);
        break;

      case gecko_evt_le_connection_closed_id:

        /* Check if need to boot to dfu mode */
        if (boot_to_dfu) {
          /* Enter to DFU OTA mode */
          gecko_cmd_system_reset(2);
        } else {
          /* Restart advertising after client has disconnected */
          gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);
        }
        break;

      /* Events related to OTA upgrading
         ----------------------------------------------------------------------------- */

      /* Check if the user-type OTA Control Characteristic was written.
       * If ota_control was written, boot the device into Device Firmware Upgrade (DFU) mode. */
      case gecko_evt_gatt_server_user_write_request_id:

        if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_ota_control) {
          /* Set flag to enter to OTA mode */
          boot_to_dfu = 1;
          /* Send response to Write Request */
          gecko_cmd_gatt_server_send_user_write_response(
            evt->data.evt_gatt_server_user_write_request.connection,
            gattdb_ota_control,
            bg_err_success);

          /* Close connection to enter to DFU OTA mode */
          gecko_cmd_le_connection_close(evt->data.evt_gatt_server_user_write_request.connection);
        }
        break;

      default:
        break;
    }
  }
}


// Setup for timer testing
//void testTimerInit(void)
//{
//	static TIMER_TypeDef     *testTimer;
//	TIMER_Init_TypeDef timerInit =
//	{
//		.enable     = true,
//		.debugRun   = true,
//		.prescale   = timerPrescale1024,
//		.clkSel     = timerClkSelHFPerClk,
//		.fallAction = timerInputActionNone,
//		.riseAction = timerInputActionNone,
//		.mode       = timerModeUp,
//		.dmaClrAct  = false,
//		.quadModeX4 = false,
//		.oneShot    = false,
//		.sync       = false,
//	};
//
//	CMU_ClockEnable(cmuClock_TIMER1, true);
//
//	testTimer = TIMER1;
//
//	TIMER_TopSet(testTimer, 3906); // ~0.5 seconds
//
//	TIMER_IntEnable(testTimer, TIMER_IF_OF);
//	NVIC_EnableIRQ(TIMER1_IRQn);
//	TIMER_Init(testTimer, &timerInit);
//
//}

//void TIMER1_IRQHandler(void)
//{
//	/* Clear flag for TIMER0 overflow interrupt */
//	TIMER_IntClear(TIMER1, TIMER_IF_OF);
//}

void ledsToggle(void)
{
	static int ledEnable = 1;
	uint8_t r, g, b;
	uint8_t m;
	uint8_t statusCode;
	uint8_t enableMask;

	m = 0xFF;
	r = 0xFF;
	g = 0xFF;
	b = 0xFF;

	enableMask = m & 0xF;

	/* Toggle LED ON/OFF */
	ledEnable *= -1;
	if(ledEnable == 1)
	{
		BOARD_rgbledEnable(true, enableMask);
	}
	else
	{
		BOARD_rgbledEnable(false, enableMask);
	}

	BOARD_rgbledSetColor(r, g, b);
}

void accelerometerSetThreshold(void)
{
	uint8_t womThreshold = 250;

	ICM20648_init();
	ICM20648_sensorEnable( true, true, true );
	//ICM20648_accelGyroCalibrate( accelBias, gyroBias );

	/* Filter bandwidth: 12kHz, otherwise the results may be off */
	ICM20648_accelBandwidthSet(ICM20648_ACCEL_BW_1210HZ);
	ICM20648_gyroBandwidthSet(ICM20648_GYRO_BW_51HZ);

	/* Accel: 2G full scale */
	ICM20648_accelFullscaleSet(ICM20648_ACCEL_FULLSCALE_16G);

	ICM20648_wakeOnMotionITEnable( true, womThreshold, 500.f );
	BOARD_imuEnableIRQ( true );
	BOARD_imuSetIRQCallback(ledsToggle);
}

void startTimerCounter(void)
 {

 }

/** @} (end addtogroup app) */
/** @} (end addtogroup Application) */
