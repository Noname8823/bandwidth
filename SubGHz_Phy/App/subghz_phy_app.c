
/*
 * STM32WLE5 - LoRa Continuous TX
 *
 * Mode 0: Continuous LoRa packets
 * Mode 1: Continuous Wave (CW)
 *
 * Frequency: 433 MHz
 * TX Power : 10 dBm
 * SF       : SF7
 * Bandwidth: 125 kHz
 */

#include <stdint.h>
#include <string.h>

#include "platform.h"
#include "sys_app.h"
#include "subghz_phy_app.h"
#include "radio.h"

#include "stm32_timer.h"
#include "stm32_seq.h"
#include "utilities_def.h"
#include "main.h"

/* ======================================
 * Configuration checks
 * ====================================== */

#if (USE_MODEM_LORA != 1) || (USE_MODEM_FSK != 0)
#error "This RF test uses LoRa only"
#endif

#if (RF_TEST_MODE != 0) && (RF_TEST_MODE != 1)
#error "RF_TEST_MODE must be 0 or 1"
#endif

#if PAYLOAD_LEN > 255
#error "PAYLOAD_LEN must be <= 255"
#endif

#define TX_TIMEOUT_MS 3000U

/* ======================================
 * TX LED - PA11
 * Assumes LED active HIGH
 * ====================================== */

#define TX_LED_ON() \
    HAL_GPIO_WritePin( \
        Led_Signal_GPIO_Port, \
        Led_Signal_Pin, \
        GPIO_PIN_SET)

#define TX_LED_OFF() \
    HAL_GPIO_WritePin( \
        Led_Signal_GPIO_Port, \
        Led_Signal_Pin, \
        GPIO_PIN_RESET)

/* ======================================
 * Global variables
 * ====================================== */

static RadioEvents_t RadioEvents;

static uint8_t BufferTx[PAYLOAD_LEN];

#if RF_TEST_MODE == 0

static UTIL_TIMER_Object_t txGapTimer;

static volatile uint32_t txDoneCount = 0;
static volatile uint32_t txTimeoutCount = 0;

#endif

/* ======================================
 * Function prototypes
 * ====================================== */

static void OnTxDone(void);
static void OnTxTimeout(void);

static void OnRxDone(
    uint8_t *payload,
    uint16_t size,
    int16_t rssi,
    int8_t loraSnr
);

static void OnRxTimeout(void);
static void OnRxError(void);

/* ======================================
 * Continuous TX Process
 * ====================================== */

#if RF_TEST_MODE == 0

static void ContinuousTx_Process(void)
{
    /* Prepare radio for TX */
    Radio.Sleep();

    /* Turn ON PA11 LED */
    TX_LED_ON();

    /* Send LoRa packet */
    Radio.Send(BufferTx, PAYLOAD_LEN);
}

/* ======================================
 * Gap timer callback
 * ====================================== */

static void OnTxGapElapsed(void *context)
{
    (void)context;

    /* Schedule next TX */
    UTIL_SEQ_SetTask(
        (1U << CFG_SEQ_Task_SubGHz_Phy_App_Process),
        CFG_SEQ_Prio_0
    );
}

#endif

/* ======================================
 * TX Done Callback
 * ====================================== */

static void OnTxDone(void)
{
    /* TX finished */
    TX_LED_OFF();

#if RF_TEST_MODE == 0

    txDoneCount++;

    /* Start delay before next packet */
    UTIL_TIMER_Start(&txGapTimer);

#endif
}

/* ======================================
 * TX Timeout Callback
 * ====================================== */

static void OnTxTimeout(void)
{
    TX_LED_OFF();

#if RF_TEST_MODE == 0

    txTimeoutCount++;

    APP_LOG(
        TS_OFF,
        VLEVEL_M,
        "TX timeout; retry\r\n"
    );

    /* Retry after delay */
    UTIL_TIMER_Start(&txGapTimer);

#else

    APP_LOG(
        TS_OFF,
        VLEVEL_M,
        "CW test finished\r\n"
    );

#endif
}

/* ======================================
 * RX Callbacks - Not used
 * ====================================== */

static void OnRxDone(
    uint8_t *payload,
    uint16_t size,
    int16_t rssi,
    int8_t loraSnr
)
{
    (void)payload;
    (void)size;
    (void)rssi;
    (void)loraSnr;
}

static void OnRxTimeout(void)
{
}

static void OnRxError(void)
{
}

/* ======================================
 * SubGHz Application Initialization
 * ====================================== */

void SubghzApp_Init(void)
{
    /* Turn OFF TX LED */
    TX_LED_OFF();

    /* Register radio callbacks */
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.TxTimeout = OnTxTimeout;

    RadioEvents.RxDone = OnRxDone;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;

    /* Initialize radio */
    Radio.Init(&RadioEvents);

    /* Set RF frequency */
    Radio.SetChannel(RF_FREQUENCY);

    /* ==================================
     * LoRa TX configuration
     * ================================== */

    Radio.SetTxConfig(
        MODEM_LORA,
        TX_OUTPUT_POWER,
        0,
        LORA_BANDWIDTH,
        LORA_SPREADING_FACTOR,
        LORA_CODINGRATE,
        LORA_PREAMBLE_LENGTH,
        LORA_FIX_LENGTH_PAYLOAD_ON,
        true,  /* CRC ON */
        0,
        0,
        LORA_IQ_INVERSION_ON,
        TX_TIMEOUT_MS
    );

    Radio.SetMaxPayloadLength(
        MODEM_LORA,
        PAYLOAD_LEN
    );

    APP_LOG(
        TS_OFF,
        VLEVEL_M,
        "RF TEST: %lu Hz, %d dBm, SF%d, "
        "BW125, %d bytes\r\n",
        (unsigned long)RF_FREQUENCY,
        TX_OUTPUT_POWER,
        LORA_SPREADING_FACTOR,
        PAYLOAD_LEN
    );

#if RF_TEST_MODE == 0

    /* ==================================
     * Mode 0: Continuous LoRa Packet
     * ================================== */

    /* Clear TX buffer */
    memset(
        BufferTx,
        0,
        sizeof(BufferTx)
    );

    /* Fill test message */
    {
        static const char message[] =
            "STM32WL_RF_SPECTRUM_TEST";

        memcpy(
            BufferTx,
            message,
            sizeof(message) - 1U
        );
    }

    /* Initialize TX gap timer */
    UTIL_TIMER_Create(
        &txGapTimer,
        RF_TEST_PACKET_GAP_MS,
        UTIL_TIMER_ONESHOT,
        OnTxGapElapsed,
        NULL
    );

    /* Register continuous TX task */
    UTIL_SEQ_RegTask(
        (1U << CFG_SEQ_Task_SubGHz_Phy_App_Process),
        UTIL_SEQ_RFU,
        ContinuousTx_Process
    );

    APP_LOG(
        TS_OFF,
        VLEVEL_M,
        "MODE: Continuous LoRa Packet\r\n"
    );

    /* Start first TX */
    UTIL_SEQ_SetTask(
        (1U << CFG_SEQ_Task_SubGHz_Phy_App_Process),
        CFG_SEQ_Prio_0
    );

#else

    /* ==================================
     * Mode 1: Continuous Wave
     * ================================== */

    APP_LOG(
        TS_OFF,
        VLEVEL_M,
        "MODE: Continuous Wave\r\n"
    );

    TX_LED_ON();

    /* Transmit CW for configured seconds */
    Radio.SetTxContinuousWave(
        RF_FREQUENCY,
        TX_OUTPUT_POWER,
        RF_TEST_CW_SECONDS
    );

#endif
}
