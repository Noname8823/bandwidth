
#ifndef __SUBGHZ_PHY_APP_H__
#define __SUBGHZ_PHY_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#define LED_ON   0
#define LED_OFF  1

/* Modem */
#define USE_MODEM_LORA                 1
#define USE_MODEM_FSK                  0

/* RF configuration */
#define RF_FREQUENCY                   433000000U
#define TX_OUTPUT_POWER                0

/*
 * RF_TEST_MODE:
 * 0 = Continuous LoRa Packet
 * 1 = Continuous Wave (CW)
 */
#define RF_TEST_MODE                   0

/* Delay between packets */
#define RF_TEST_PACKET_GAP_MS          10U

/* CW duration (seconds) */
#define RF_TEST_CW_SECONDS             15U

/* LoRa configuration */
#define LORA_BANDWIDTH                 0
#define LORA_SPREADING_FACTOR          7
#define LORA_CODINGRATE                1
#define LORA_PREAMBLE_LENGTH           8
#define LORA_SYMBOL_TIMEOUT           5

#define LORA_FIX_LENGTH_PAYLOAD_ON     false
#define LORA_IQ_INVERSION_ON           false

/* Payload size */
#define PAYLOAD_LEN                    64

/* Functions */
void SubghzApp_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __SUBGHZ_PHY_APP_H__ */
