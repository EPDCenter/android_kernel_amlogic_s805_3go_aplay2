#ifndef  TUNER_Si2191_SPECIFICS
#define  TUNER_Si2191_SPECIFICS
/* Change log:
  As from V2.6.3:
   Removed LO_INJECTION macros (same settings for ATV and DTV)
*/

    #include "Si2191_L2_API.h"

#ifdef    SILABS_EVB
    #define Si2168_CLOCK_MODE_TER              Si2168_START_CLK_CMD_CLK_MODE_CLK_CLKIO
    #define Si2168_REF_FREQUENCY_TER           24
#else  /* SILABS_EVB */
    #define Si2168_CLOCK_MODE_TER              Si2168_START_CLK_CMD_CLK_MODE_CLK_CLKIO
    #define Si2168_REF_FREQUENCY_TER           24
#endif /* SILABS_EVB */

    #define TUNERTER_API
    #define TER_TUNER_CONTEXT            L1_Si2191_Context
    #define TUNER_ADDRESS_TER            0xc0

    #define TER_TUNER_INIT(api)           Si2191_Init(api)
    #define TER_TUNER_AGC_EXTERNAL(api)   api->prop->dtv_config_if_port.dtv_out_type    = Si2191_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1;\
                                          api->prop->dtv_config_if_port.dtv_agc_source  = Si2191_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_AGC1_3DB;\
                                          Si2191_L1_SetProperty2(api, Si2191_DTV_CONFIG_IF_PORT_PROP_CODE);

    #define TER_TUNER_WAKEUP(api)         Si2191_pollForCTS(api)
    /* Compatibility with Si2191 ROM12 & ROM13 APIs */
   #ifdef    Si2191_STANDBY_CMD_TYPE_MIN
     #define TER_TUNER_STANDBY(api)        Si2191_L1_STANDBY(api, Si2191_STANDBY_CMD_TYPE_MIN)
   #else  /* Si2191_STANDBY_CMD_TYPE_MIN */
    #define TER_TUNER_STANDBY(api)        Si2191_L1_STANDBY(api)
   #endif /* Si2191_STANDBY_CMD_TYPE_MIN */
    #define TER_TUNER_CLOCK_OFF(api)      Si2191_XoutOff(api)
    #define TER_TUNER_CLOCK_ON(api)       Si2191_XoutOn(api)
    #define TER_TUNER_ERROR_TEXT(res)     Si2191_L1_API_ERROR_TEXT(res)
#ifdef    Si2168_COMMAND_LINE_APPLICATION
    #define TER_TUNER_MENU(full)          Si2191_menu(full)
    #define TER_TUNER_LOOP(api,choice)    Si2191_demoLoop(api,choice)
#endif /* Si2168_COMMAND_LINE_APPLICATION */

    #define TER_TUNER_MODULATION_DVBT     Si2191_DTV_MODE_PROP_MODULATION_DVBT
    #define TER_TUNER_MODULATION_DVBC     Si2191_DTV_MODE_PROP_MODULATION_DVBC

    #define L1_RF_TER_TUNER_Init(api,add) Si2191_L1_API_Init(api, add);
    #define L1_RF_TER_TUNER_Tune(api,rf)  Si2191_DTVTune(api, rf, bw, modulation, Si2191_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL); system_wait(85);

    #define L1_RF_TER_TUNER_Get_RF

    #define L1_RF_TER_TUNER_MODULATION_DVBC  Si2191_DTV_MODE_PROP_MODULATION_DVBC
    #define L1_RF_TER_TUNER_MODULATION_DVBT  Si2191_DTV_MODE_PROP_MODULATION_DVBT
    #define L1_RF_TER_TUNER_MODULATION_DVBT2 Si2191_DTV_MODE_PROP_MODULATION_DVBT

    #define   L1_RF_TER_TUNER_FEF_MODE_FREEZE_PIN_SETUP(api) \
    api->cmd->config_pins.gpio1_mode               = Si2191_CONFIG_PINS_CMD_GPIO1_MODE_DISABLE;\
    api->cmd->config_pins.gpio1_read               = Si2191_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ;\
    api->cmd->config_pins.gpio2_mode               = Si2191_CONFIG_PINS_CMD_GPIO2_MODE_DISABLE;\
    api->cmd->config_pins.gpio2_read               = Si2191_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ;\
    api->cmd->config_pins.reserved1                = Si2191_CONFIG_PINS_CMD_RESERVED1_RESERVED;\
    api->cmd->config_pins.reserved2                = Si2191_CONFIG_PINS_CMD_RESERVED2_RESERVED;\
    api->cmd->config_pins.reserved3                = Si2191_CONFIG_PINS_CMD_RESERVED3_RESERVED;\
    api->prop->dtv_initial_agc_speed.agc_decim     = Si2191_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF;\
    api->prop->dtv_initial_agc_speed.if_agc_speed  = Si2191_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;\
    api->prop->dtv_initial_agc_speed_period.period = 0;\
    api->prop->dtv_agc_speed.agc_decim             = Si2191_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;\
    api->prop->dtv_agc_speed.if_agc_speed          = Si2191_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;\
    Si2191_L1_SendCommand2(api, Si2191_CONFIG_PINS_CMD_CODE);\
    Si2191_L1_SetProperty2(api, Si2191_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE);\
    Si2191_L1_SetProperty2(api, Si2191_DTV_AGC_SPEED_PROP_CODE);

    #define   L1_RF_TER_TUNER_FEF_MODE_FREEZE_PIN(api,fef) \
    api->prop->dtv_agc_freeze_input.level          = Si2191_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_HIGH;\
    if (fef == 0) {\
      api->prop->dtv_agc_freeze_input.pin          = Si2191_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE;\
    } else {\
      api->prop->dtv_agc_freeze_input.pin          = Si2191_DTV_AGC_FREEZE_INPUT_PROP_PIN_GPIO1;\
    }\
    Si2191_L1_SetProperty2(api, Si2191_DTV_AGC_FREEZE_INPUT_PROP_CODE);

    #define   L1_RF_TER_TUNER_FEF_MODE_SLOW_INITIAL_AGC_SETUP(api,fef) \
      if (fef == 0) {\
        api->prop->dtv_initial_agc_speed.agc_decim     = Si2191_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF;\
        api->prop->dtv_initial_agc_speed.if_agc_speed  = Si2191_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;\
        api->prop->dtv_initial_agc_speed_period.period = 0;\
        api->prop->dtv_agc_speed.agc_decim             = Si2191_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;\
        api->prop->dtv_agc_speed.if_agc_speed          = Si2191_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;\
      } else {\
        api->prop->dtv_initial_agc_speed.agc_decim     = Si2191_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF;\
        api->prop->dtv_initial_agc_speed.if_agc_speed  = Si2191_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;\
        api->prop->dtv_initial_agc_speed_period.period = 240;\
        api->prop->dtv_agc_speed.agc_decim             = Si2191_DTV_AGC_SPEED_PROP_AGC_DECIM_4;\
        api->prop->dtv_agc_speed.if_agc_speed          = Si2191_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39;\
      }\
      Si2191_L1_SetProperty2(api, Si2191_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE);\
      Si2191_L1_SetProperty2(api, Si2191_DTV_AGC_SPEED_PROP_CODE);


    #define   L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC_SETUP(api,fef) \
      api->prop->dtv_initial_agc_speed_period.period = 0;\
      if (fef == 0) {\
        api->prop->dtv_agc_speed.agc_decim             = Si2191_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;\
        api->prop->dtv_agc_speed.if_agc_speed          = Si2191_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;\
      } else {\
        api->prop->dtv_agc_speed.if_agc_speed          = Si2191_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39;\
        api->prop->dtv_agc_speed.agc_decim             = Si2191_DTV_AGC_SPEED_PROP_AGC_DECIM_4;\
      }\
      Si2191_L1_SetProperty2(api, Si2191_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE);\
      Si2191_L1_SetProperty2(api, Si2191_DTV_AGC_SPEED_PROP_CODE);

    #define   L1_RF_TER_TUNER_FEF_MODE_SLOW_NORMAL_AGC(api,fef) \
      if (fef == 0) {\
        api->prop->dtv_agc_speed.agc_decim             = Si2191_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;\
        api->prop->dtv_agc_speed.if_agc_speed          = Si2191_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;\
      } else {\
        api->prop->dtv_agc_speed.if_agc_speed          = Si2191_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39;\
        api->prop->dtv_agc_speed.agc_decim             = Si2191_DTV_AGC_SPEED_PROP_AGC_DECIM_4;\
      }\
      Si2191_L1_SetProperty2(api, Si2191_DTV_AGC_SPEED_PROP_CODE);

#endif /* TUNER_Si2191_SPECIFICS */

