/* SPDX-License-Identifier: ISC */
/* Copyright (C) 2020 MediaTek Inc. */

#ifndef __MT7902_MCU_H
#define __MT7902_MCU_H

#include "../mt76_connac_mcu.h"

struct mt7902_mcu_tx_done_event {
	u8 pid;
	u8 status;
	__le16 seq;

	u8 wlan_idx;
	u8 tx_cnt;
	__le16 tx_rate;

	u8 flag;
	u8 tid;
	u8 rsp_rate;
	u8 mcs;

	u8 bw;
	u8 tx_pwr;
	u8 reason;
	u8 rsv0[1];

	__le32 delay;
	__le32 timestamp;
	__le32 applied_flag;
	u8 txs[28];

	u8 rsv1[32];
} __packed;

/* ext event table */
enum {
	MCU_EXT_EVENT_RATE_REPORT = 0x87,
};

struct mt7902_mcu_eeprom_info {
	__le32 addr;
	__le32 valid;
	u8 data[MT7902_EEPROM_BLOCK_SIZE];
} __packed;

#define MT_RA_RATE_NSS			GENMASK(8, 6)
#define MT_RA_RATE_MCS			GENMASK(3, 0)
#define MT_RA_RATE_TX_MODE		GENMASK(12, 9)
#define MT_RA_RATE_DCM_EN		BIT(4)
#define MT_RA_RATE_BW			GENMASK(14, 13)

enum {
	MT_EBF = BIT(0),	/* explicit beamforming */
	MT_IBF = BIT(1)		/* implicit beamforming */
};

struct mt7902_mcu_ant_id_config {
	u8 ant_id[4];
} __packed;

struct mt7902_txpwr_req {
	u8 ver;
	u8 action;
	__le16 len;
	u8 dbdc_idx;
	u8 rsv[3];
} __packed;

struct mt7902_txpwr_event {
	u8 ver;
	u8 action;
	__le16 len;
	struct mt7902_txpwr txpwr;
} __packed;

struct mt7902_wf_rf_pin_ctrl_event {
	u8 result;
	u8 value;
} __packed;

enum {
	TM_SWITCH_MODE,
	TM_SET_AT_CMD,
	TM_QUERY_AT_CMD,
};

enum {
	MT7902_TM_NORMAL,
	MT7902_TM_TESTMODE,
	MT7902_TM_ICAP,
	MT7902_TM_ICAP_OVERLAP,
	MT7902_TM_WIFISPECTRUM,
};

struct mt7902_rftest_cmd {
	u8 action;
	u8 rsv[3];
	__le32 param0;
	__le32 param1;
} __packed;

struct mt7902_rftest_evt {
	__le32 param0;
	__le32 param1;
} __packed;

struct mt7902_clc_info_tlv {
	__le16 tag;
	__le16 len;

	u8 chan_conf; /* BIT(0) : Enable UNII-4
		       * BIT(1) : Enable UNII-5
		       * BIT(2) : Enable UNII-6
		       * BIT(3) : Enable UNII-7
		       * BIT(4) : Enable UNII-8
		       */
	u8 rsv[63];
} __packed;


struct bss_info_bmc_rate {
	__le16 tag;
	__le16 len;
	__le16 bc_trans;
	__le16 mc_trans;
	u8 short_preamble;
	u8 rsv[7];
} __packed;

struct bss_info_ra {
	__le16 tag;
	__le16 len;
	u8 op_mode;
	u8 adhoc_en;
	u8 short_preamble;
	u8 tx_streams;
	u8 rx_streams;
	u8 algo;
	u8 force_sgi;
	u8 force_gf;
	u8 ht_mode;
	u8 has_20_sta;		/* Check if any sta support GF. */
	u8 bss_width_trigger_events;
	u8 vht_nss_cap;
	u8 vht_bw_signal;	/* not use */
	u8 vht_force_sgi;	/* not use */
	u8 se_off;
	u8 antenna_idx;
	u8 train_up_rule;
	u8 rsv[3];
	unsigned short train_up_high_thres;
	short train_up_rule_rssi;
	unsigned short low_traffic_thres;
	__le16 max_phyrate;
	__le32 phy_cap;
	__le32 interval;
	__le32 fast_interval;
} __packed;

struct bss_info_hw_amsdu {
	__le16 tag;
	__le16 len;
	__le32 cmp_bitmap_0;
	__le32 cmp_bitmap_1;
	__le16 trig_thres;
	u8 enable;
	u8 rsv;
} __packed;

struct bss_info_he {
	__le16 tag;
	__le16 len;
	u8 he_pe_duration;
	u8 vht_op_info_present;
	__le16 he_rts_thres;
	__le16 max_nss_mcs[CMD_HE_MCS_BW_NUM];
	u8 rsv[6];
} __packed;

#define MT7902_BSS_UPDATE_MAX_SIZE	(sizeof(struct sta_req_hdr) +	\
					 sizeof(struct bss_info_omac) +	\
					 sizeof(struct bss_info_basic) +\
					 sizeof(struct bss_info_rf_ch) +\
					 sizeof(struct bss_info_ra) +	\
					 sizeof(struct bss_info_hw_amsdu) +\
					 sizeof(struct bss_info_he) +	\
					 sizeof(struct bss_info_bmc_rate) +\
					 sizeof(struct bss_info_ext_bss))

#endif
