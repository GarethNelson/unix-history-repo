/*-
 * Copyright (c) 2008, Pyun YongHyeon <yongari@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef	_IF_JMEREG_H
#define	_IF_JMEREG_H

/*
 * JMicron Inc. PCI vendor ID
 */
#define	VENDORID_JMICRON	0x197B

/*
 * JMC250 PCI device ID
 */
#define	DEVICEID_JMC250		0x0250
#define	DEVICEREVID_JMC250_A0	0x00
#define	DEVICEREVID_JMC250_A2	0x11

/*
 * JMC260 PCI device ID
 */
#define	DEVICEID_JMC260		0x0260
#define	DEVICEREVID_JMC260_A0	0x00

#define	DEVICEID_JMC2XX_MASK	0x0FF0

/* JMC250 PCI configuration register. */
#define	JME_PCI_BAR0		0x10	/* 16KB memory window. */

#define	JME_PCI_BAR1		0x18	/* 128bytes I/O window. */

#define	JME_PCI_BAR2		0x1C	/* 256bytes I/O window. */

#define	JME_PCI_BAR3		0x20	/* 64KB memory window. */

#define	JME_PCI_EROM		0x30

#define	JME_PCI_DBG		0x9C

#define	JME_PCI_SPI		0xB0

#define	SPI_ENB			0x00000010
#define	SPI_SO_STATUS		0x00000008
#define	SPI_SI_CTRL		0x00000004
#define	SPI_SCK_CTRL		0x00000002
#define	SPI_CS_N_CTRL		0x00000001

#define	JME_PCI_PHYCFG0		0xC0

#define	JME_PCI_PHYCFG1		0xC4

#define	JME_PCI_PHYCFG2		0xC8

#define	JME_PCI_PHYCFG3		0xCC

#define	JME_PCI_PIPECTL1	0xD0

#define	JME_PCI_PIPECTL2	0xD4

/* PCIe link error/status. */
#define	JME_PCI_LES		0xD8

/* propeietary register 0. */
#define	JME_PCI_PE0		0xE0
#define	PE0_SPI_EXIST		0x00200000
#define	PE0_PME_D0		0x00100000
#define	PE0_PME_D3H		0x00080000
#define	PE0_PME_SPI_PAD		0x00040000
#define	PE0_MASK_ASPM		0x00020000
#define	PE0_EEPROM_RW_DIS	0x00008000
#define	PE0_PCI_INTA		0x00001000
#define	PE0_PCI_INTB		0x00002000
#define	PE0_PCI_INTC		0x00003000
#define	PE0_PCI_INTD		0x00004000
#define	PE0_PCI_SVSSID_WR_ENB	0x00000800
#define	PE0_MSIX_SIZE_8		0x00000700
#define	PE0_MSIX_SIZE_7		0x00000600
#define	PE0_MSIX_SIZE_6		0x00000500
#define	PE0_MSIX_SIZE_5		0x00000400
#define	PE0_MSIX_SIZE_4		0x00000300
#define	PE0_MSIX_SIZE_3		0x00000200
#define	PE0_MSIX_SIZE_2		0x00000100
#define	PE0_MSIX_SIZE_1		0x00000000
#define	PE0_MSIX_SIZE_DEF	0x00000700
#define	PE0_MSIX_CAP_DIS	0x00000080
#define	PE0_MSI_PVMC_ENB	0x00000040
#define	PE0_LCAP_EXIT_LAT_MASK	0x00000038
#define	PE0_LCAP_EXIT_LAT_DEF	0x00000038
#define	PE0_PM_AUXC_MASK	0x00000007
#define	PE0_PM_AUXC_DEF		0x00000007

#define	JME_PCI_PE1		0xE4

#define	JME_PCI_PHYTEST		0xF8

#define	JME_PCI_GPR		0xFC

/*
 * JMC Register Map.
 * -----------------------------------------------------------------------
 *   Register               Size           IO space         Memory space
 * -----------------------------------------------------------------------
 * Tx/Rx MAC registers    128 bytes     BAR1 + 0x00 ~       BAR0 + 0x00 ~
 *                                       BAR1 + 0x7F         BAR0 + 0x7F
 * -----------------------------------------------------------------------
 * PHY registers          128 bytes     BAR2 + 0x00 ~       BAR0 + 0x400 ~
 *                                       BAR2 + 0x7F         BAR0 + 0x47F
 * -----------------------------------------------------------------------
 * Misc registers         128 bytes     BAR2 + 0x80 ~       BAR0 + 0x800 ~
 *                                       BAR2 + 0x7F         BAR0 + 0x87F
 * -----------------------------------------------------------------------
 * To simplify register access fuctions and to get better performance
 * this driver doesn't support IO space access. It could be implemented
 * as a function which selects appropriate BARs to access requested
 * register.
 */

/* Tx control and status. */
#define	JME_TXCSR		0x0000
#define	TXCSR_QWEIGHT_MASK	0x0F000000
#define	TXCSR_QWEIGHT_SHIFT	24
#define	TXCSR_TXQ_SEL_MASK	0x00070000
#define	TXCSR_TXQ_SEL_SHIFT	16
#define	TXCSR_TXQ_START		0x00000001
#define	TXCSR_TXQ_START_SHIFT	8
#define	TXCSR_FIFO_THRESH_4QW	0x00000000
#define	TXCSR_FIFO_THRESH_8QW	0x00000040
#define	TXCSR_FIFO_THRESH_12QW	0x00000080
#define	TXCSR_FIFO_THRESH_16QW	0x000000C0
#define	TXCSR_DMA_SIZE_64	0x00000000
#define	TXCSR_DMA_SIZE_128	0x00000010
#define	TXCSR_DMA_SIZE_256	0x00000020
#define	TXCSR_DMA_SIZE_512	0x00000030
#define	TXCSR_DMA_BURST		0x00000004
#define	TXCSR_TX_SUSPEND	0x00000002
#define	TXCSR_TX_ENB		0x00000001
#define	TXCSR_TXQ0		0
#define	TXCSR_TXQ1		1
#define	TXCSR_TXQ2		2
#define	TXCSR_TXQ3		3
#define	TXCSR_TXQ4		4
#define	TXCSR_TXQ5		5
#define	TXCSR_TXQ6		6
#define	TXCSR_TXQ7		7
#define	TXCSR_TXQ_WEIGHT(x)	\
	(((x) << TXCSR_QWEIGHT_SHIFT) & TXCSR_QWEIGHT_MASK)
#define	TXCSR_TXQ_WEIGHT_MIN	0
#define	TXCSR_TXQ_WEIGHT_MAX	15
#define	TXCSR_TXQ_N_SEL(x)	\
	(((x) << TXCSR_TXQ_SEL_SHIFT) & TXCSR_TXQ_SEL_MASK)
#define	TXCSR_TXQ_N_START(x)	\
	(TXCSR_TXQ_START << (TXCSR_TXQ_START_SHIFT + (x)))

/* Tx queue descriptor base address. 16bytes alignment required. */
#define	JME_TXDBA_LO		0x0004
#define	JME_TXDBA_HI		0x0008

/* Tx queue descriptor count. multiple of 16(max = 1024). */
#define	JME_TXQDC		0x000C
#define	TXQDC_MASK		0x0000007F0

/* Tx queue next descriptor address. */
#define	JME_TXNDA		0x0010
#define	TXNDA_ADDR_MASK		0xFFFFFFF0
#define	TXNDA_DESC_EMPTY	0x00000008
#define	TXNDA_DESC_VALID	0x00000004
#define	TXNDA_DESC_WAIT		0x00000002
#define	TXNDA_DESC_FETCH	0x00000001

/* Tx MAC control ans status. */
#define	JME_TXMAC		0x0014
#define	TXMAC_IFG2_MASK		0xC0000000
#define	TXMAC_IFG2_DEFAULT	0x40000000
#define	TXMAC_IFG1_MASK		0x30000000
#define	TXMAC_IFG1_DEFAULT	0x20000000
#define	TXMAC_PAUSE_CNT_MASK	0x00FF0000
#define	TXMAC_THRESH_1_PKT	0x00000300
#define	TXMAC_THRESH_1_2_PKT	0x00000200
#define	TXMAC_THRESH_1_4_PKT	0x00000100
#define	TXMAC_THRESH_1_8_PKT	0x00000000
#define	TXMAC_FRAME_BURST	0x00000080
#define	TXMAC_CARRIER_EXT	0x00000040
#define	TXMAC_IFG_ENB		0x00000020
#define	TXMAC_BACKOFF		0x00000010
#define	TXMAC_CARRIER_SENSE	0x00000008
#define	TXMAC_COLL_ENB		0x00000004
#define	TXMAC_CRC_ENB		0x00000002
#define	TXMAC_PAD_ENB		0x00000001

/* Tx pause frame control. */
#define	JME_TXPFC		0x0018
#define	TXPFC_VLAN_TAG_MASK	0xFFFF0000
#define	TXPFC_VLAN_TAG_SHIFT	16
#define	TXPFC_VLAN_ENB		0x00008000
#define	TXPFC_PAUSE_ENB		0x00000001

/* Tx timer/retry at half duplex. */
#define	JME_TXTRHD		0x001C
#define	TXTRHD_RT_PERIOD_ENB	0x80000000
#define	TXTRHD_RT_PERIOD_MASK	0x7FFFFF00
#define	TXTRHD_RT_PERIOD_SHIFT	8
#define	TXTRHD_RT_LIMIT_ENB	0x00000080
#define	TXTRHD_RT_LIMIT_MASK	0x0000007F
#define	TXTRHD_RT_LIMIT_SHIFT	0
#define	TXTRHD_RT_PERIOD_DEFAULT	8192
#define	TXTRHD_RT_LIMIT_DEFAULT	8

/* Rx control & status. */
#define	JME_RXCSR		0x0020
#define	RXCSR_FIFO_FTHRESH_16T	0x00000000
#define	RXCSR_FIFO_FTHRESH_32T	0x10000000
#define	RXCSR_FIFO_FTHRESH_64T	0x20000000
#define	RXCSR_FIFO_FTHRESH_128T	0x30000000
#define	RXCSR_FIFO_FTHRESH_MASK	0x30000000
#define	RXCSR_FIFO_THRESH_16QW	0x00000000
#define	RXCSR_FIFO_THRESH_32QW	0x04000000
#define	RXCSR_FIFO_THRESH_64QW	0x08000000	/* JMC250/JMC260 REVFM < 2 */
#define	RXCSR_FIFO_THRESH_128QW	0x0C000000	/* JMC250/JMC260 REVFM < 2 */
#define	RXCSR_FIFO_THRESH_MASK	0x0C000000
#define	RXCSR_DMA_SIZE_16	0x00000000
#define	RXCSR_DMA_SIZE_32	0x01000000
#define	RXCSR_DMA_SIZE_64	0x02000000
#define	RXCSR_DMA_SIZE_128	0x03000000
#define	RXCSR_RXQ_SEL_MASK	0x00030000
#define	RXCSR_RXQ_SEL_SHIFT	16
#define	RXCSR_DESC_RT_GAP_MASK	0x0000F000
#define	RXCSR_DESC_RT_GAP_SHIFT	12
#define	RXCSR_DESC_RT_GAP_256	0x00000000
#define	RXCSR_DESC_RT_GAP_512	0x00001000
#define	RXCSR_DESC_RT_GAP_1024	0x00002000
#define	RXCSR_DESC_RT_GAP_2048	0x00003000
#define	RXCSR_DESC_RT_GAP_4096	0x00004000
#define	RXCSR_DESC_RT_GAP_8192	0x00005000
#define	RXCSR_DESC_RT_GAP_16384	0x00006000
#define	RXCSR_DESC_RT_GAP_32768	0x00007000
#define	RXCSR_DESC_RT_CNT_MASK	0x00000F00
#define	RXCSR_DESC_RT_CNT_SHIFT	8
#define	RXCSR_PASS_WAKEUP_PKT	0x00000040
#define	RXCSR_PASS_MAGIC_PKT	0x00000020
#define	RXCSR_PASS_RUNT_PKT	0x00000010
#define	RXCSR_PASS_BAD_PKT	0x00000008
#define	RXCSR_RXQ_START		0x00000004
#define	RXCSR_RX_SUSPEND	0x00000002
#define	RXCSR_RX_ENB		0x00000001

#define	RXCSR_RXQ_N_SEL(x)	((x) << RXCSR_RXQ_SEL_SHIFT)
#define	RXCSR_RXQ0		0
#define	RXCSR_RXQ1		1
#define	RXCSR_RXQ2		2
#define	RXCSR_RXQ3		3
#define	RXCSR_DESC_RT_CNT(x)	\
	(((x) << RXCSR_DESC_RT_CNT_SHIFT) & RXCSR_DESC_RT_CNT_MASK)
#define	RXCSR_DESC_RT_CNT_DEFAULT	0

/* Rx queue descriptor base address. 16bytes alignment needed. */
#define	JME_RXDBA_LO		0x0024
#define	JME_RXDBA_HI		0x0028

/* Rx queue descriptor count. multiple of 16(max = 1024). */
#define	JME_RXQDC		0x002C
#define	RXQDC_MASK		0x0000007F0

/* Rx queue next descriptor address. */
#define	JME_RXNDA		0x0030
#define	RXNDA_ADDR_MASK		0xFFFFFFF0
#define	RXNDA_DESC_EMPTY	0x00000008
#define	RXNDA_DESC_VALID	0x00000004
#define	RXNDA_DESC_WAIT		0x00000002
#define	RXNDA_DESC_FETCH	0x00000001

/* Rx MAC control and status. */
#define	JME_RXMAC		0x0034
#define	RXMAC_RSS_UNICAST	0x00000000
#define	RXMAC_RSS_UNI_MULTICAST	0x00010000
#define	RXMAC_RSS_UNI_MULTI_BROADCAST	0x00020000
#define	RXMAC_RSS_ALLFRAME	0x00030000
#define	RXMAC_PROMISC		0x00000800
#define	RXMAC_BROADCAST		0x00000400
#define	RXMAC_MULTICAST		0x00000200
#define	RXMAC_UNICAST		0x00000100
#define	RXMAC_ALLMULTI		0x00000080
#define	RXMAC_MULTICAST_FILTER	0x00000040
#define	RXMAC_COLL_DET_ENB	0x00000020
#define	RXMAC_FC_ENB		0x00000008
#define	RXMAC_VLAN_ENB		0x00000004
#define	RXMAC_PAD_10BYTES	0x00000002
#define	RXMAC_CSUM_ENB		0x00000001

/* Rx unicast MAC address. */
#define	JME_PAR0		0x0038
#define	JME_PAR1		0x003C

/* Rx multicast address hash table. */
#define	JME_MAR0		0x0040
#define	JME_MAR1		0x0044

/* Wakeup frame output data port. */
#define	JME_WFODP		0x0048

/* Wakeup frame output interface. */
#define	JME_WFOI		0x004C
#define	WFOI_MASK_0_31		0x00000000
#define	WFOI_MASK_31_63		0x00000010
#define	WFOI_MASK_64_95		0x00000020
#define	WFOI_MASK_96_127	0x00000030
#define	WFOI_MASK_SEL		0x00000008
#define	WFOI_CRC_SEL		0x00000000
#define	WFOI_WAKEUP_FRAME_MASK	0x00000007
#define	WFOI_WAKEUP_FRAME_SEL(x)	((x) & WFOI_WAKEUP_FRAME_MASK)

/* Station management interface. */
#define	JME_SMI			0x0050
#define	SMI_DATA_MASK		0xFFFF0000
#define	SMI_DATA_SHIFT		16
#define	SMI_REG_ADDR_MASK	0x0000F800
#define	SMI_REG_ADDR_SHIFT	11
#define	SMI_PHY_ADDR_MASK	0x000007C0
#define	SMI_PHY_ADDR_SHIFT	6
#define	SMI_OP_WRITE		0x00000020
#define	SMI_OP_READ		0x00000000
#define	SMI_OP_EXECUTE		0x00000010
#define	SMI_MDIO		0x00000008
#define	SMI_MDOE		0x00000004
#define	SMI_MDC			0x00000002
#define	SMI_MDEN		0x00000001
#define	SMI_REG_ADDR(x)		\
	(((x) << SMI_REG_ADDR_SHIFT) & SMI_REG_ADDR_MASK)
#define	SMI_PHY_ADDR(x)		\
	(((x) << SMI_PHY_ADDR_SHIFT) & SMI_PHY_ADDR_MASK)

/* Global host control. */
#define	JME_GHC			0x0054
#define	GHC_LOOPBACK		0x80000000
#define	GHC_RESET		0x40000000
#define	GHC_RX_DMA_PWR_DIS	0x04000000	/* JMC250 REVFM >= 2 */
#define	GHC_FIFO_RD_PWR_DIS	0x02000000	/* JMC250 REVFM >= 2 */
#define	GHC_FIFO_WR_PWR_DIS	0x01000000	/* JMC250 REVFM >= 2 */
#define	GHC_TX_OFFLD_CLK_100	0x00800000	/* JMC250/JMC260 REVFM >= 2 */
#define	GHC_TX_OFFLD_CLK_1000	0x00400000	/* JMC250/JMC260 REVFM >= 2 */
#define	GHC_TX_OFFLD_CLK_DIS	0x00000000	/* JMC250/JMC260 REVFM >= 2 */
#define	GHC_TX_MAC_CLK_100	0x00200000	/* JMC250/JMC260 REVFM >= 2 */
#define	GHC_TX_MAC_CLK_1000	0x00100000	/* JMC250/JMC260 REVFM >= 2 */
#define	GHC_TX_MAC_CLK_DIS	0x00000000	/* JMC250/JMC260 REVFM >= 2 */
#define	GHC_AUTO_PHY_STAT_DIS	0x00000080	/* JMC250/JMC260 REVFM >= 2 */
#define	GHC_FULL_DUPLEX		0x00000040
#define	GHC_SPEED_UNKNOWN	0x00000000
#define	GHC_SPEED_10		0x00000010
#define	GHC_SPEED_100		0x00000020
#define	GHC_SPEED_1000		0x00000030
#define	GHC_SPEED_MASK		0x00000030
#define	GHC_LINK_OFF		0x00000004
#define	GHC_LINK_ON		0x00000002
#define	GHC_LINK_STAT_POLLING	0x00000001

/* Power management control and status. */
#define	JME_PMCS		0x0060
#define	PMCS_WAKEUP_FRAME_7	0x80000000
#define	PMCS_WAKEUP_FRAME_6	0x40000000
#define	PMCS_WAKEUP_FRAME_5	0x20000000
#define	PMCS_WAKEUP_FRAME_4	0x10000000
#define	PMCS_WAKEUP_FRAME_3	0x08000000
#define	PMCS_WAKEUP_FRAME_2	0x04000000
#define	PMCS_WAKEUP_FRAME_1	0x02000000
#define	PMCS_WAKEUP_FRAME_0	0x01000000
#define	PMCS_LINK_FAIL		0x00040000
#define	PMCS_LINK_RISING	0x00020000
#define	PMCS_MAGIC_FRAME	0x00010000
#define	PMCS_WAKEUP_FRAME_7_ENB	0x00008000
#define	PMCS_WAKEUP_FRAME_6_ENB	0x00004000
#define	PMCS_WAKEUP_FRAME_5_ENB	0x00002000
#define	PMCS_WAKEUP_FRAME_4_ENB	0x00001000
#define	PMCS_WAKEUP_FRAME_3_ENB	0x00000800
#define	PMCS_WAKEUP_FRAME_2_ENB	0x00000400
#define	PMCS_WAKEUP_FRAME_1_ENB	0x00000200
#define	PMCS_WAKEUP_FRAME_0_ENB	0x00000100
#define	PMCS_LINK_FAIL_ENB	0x00000004
#define	PMCS_LINK_RISING_ENB	0x00000002
#define	PMCS_MAGIC_FRAME_ENB	0x00000001
#define	PMCS_WOL_ENB_MASK	0x0000FFFF

/*
 * Statistic registers control and status.
 * These statistics registers are valid only for JMC250/JMC260 REVFM >= 2.
 */
#define	JME_STATCSR		0x0064
#define	STATCSR_RXMPT_DIS	0x00000080
#define	STATCSR_OFLOW_DIS	0x00000040
#define	STATCSR_MIIRXER_DIS	0x00000020
#define	STATCSR_CRCERR_DIS	0x00000010
#define	STATCSR_RXBAD_DIS	0x00000008
#define	STATCSR_RXGOOD_DIS	0x00000004
#define	STATCSR_TXBAD_DIS	0x00000002
#define	STATCSR_TXGOOD_DIS	0x00000001

#define	JME_STAT_TXGOOD		0x0068

#define	JME_STAT_RXGOOD		0x006C

#define	JME_STAT_CRCMII		0x0070
#define	STAT_RX_CRC_ERR_MASK	0xFFFF0000
#define	STAT_RX_MII_ERR_MASK	0x0000FFFF
#define	STAT_RX_CRC_ERR_SHIFT	16
#define	STAT_RX_MII_ERR_SHIFT	0

#define	JME_STAT_RXERR		0x0074
#define	STAT_RXERR_OFLOW_MASK	0xFFFF0000
#define	STAT_RXERR_MPTY_MASK	0x0000FFFF
#define	STAT_RXERR_OFLOW_SHIFT	16
#define	STAT_RXERR_MPTY_SHIFT	0

#define	JME_STAT_RESERVED1	0x0078

#define	JME_STAT_FAIL		0x007C
#define	STAT_FAIL_RX_MASK	0xFFFF0000
#define	STAT_FAIL_TX_MASK	0x0000FFFF
#define	STAT_FAIL_RX_SHIFT	16
#define	STAT_FAIL_TX_SHIFT	0

/* Giga PHY & EEPROM registers. */
#define	JME_PHY_EEPROM_BASE_ADDR	0x0400

#define	JME_GIGAR0LO		0x0400
#define	JME_GIGAR0HI		0x0404
#define	JME_GIGARALO		0x0408
#define	JME_GIGARAHI		0x040C
#define	JME_GIGARBLO		0x0410
#define	JME_GIGARBHI		0x0414
#define	JME_GIGARCLO		0x0418
#define	JME_GIGARCHI		0x041C
#define	JME_GIGARDLO		0x0420
#define	JME_GIGARDHI		0x0424

/* BIST status and control. */
#define	JME_GIGACSR		0x0428
#define	GIGACSR_STATUS		0x40000000
#define	GIGACSR_CTRL_MASK	0x30000000
#define	GIGACSR_CTRL_DEFAULT	0x30000000
#define	GIGACSR_TX_CLK_MASK	0x0F000000
#define	GIGACSR_RX_CLK_MASK	0x00F00000
#define	GIGACSR_TX_CLK_INV	0x00080000
#define	GIGACSR_RX_CLK_INV	0x00040000
#define	GIGACSR_PHY_RST		0x00010000
#define	GIGACSR_IRQ_N_O		0x00001000
#define	GIGACSR_BIST_OK		0x00000200
#define	GIGACSR_BIST_DONE	0x00000100
#define	GIGACSR_BIST_LED_ENB	0x00000010
#define	GIGACSR_BIST_MASK	0x00000003

/* PHY Link Status. */
#define	JME_LNKSTS		0x0430
#define	LINKSTS_SPEED_10	0x00000000
#define	LINKSTS_SPEED_100	0x00004000
#define	LINKSTS_SPEED_1000	0x00008000
#define	LINKSTS_FULL_DUPLEX	0x00002000
#define	LINKSTS_PAGE_RCVD	0x00001000
#define	LINKSTS_SPDDPX_RESOLVED	0x00000800
#define	LINKSTS_UP		0x00000400
#define	LINKSTS_ANEG_COMP	0x00000200
#define	LINKSTS_MDI_CROSSOVR	0x00000040
#define	LINKSTS_LPAR_PAUSE_ASYM	0x00000002
#define	LINKSTS_LPAR_PAUSE	0x00000001

/* SMB control and status. */
#define	JME_SMBCSR		0x0440
#define	SMBCSR_SLAVE_ADDR_MASK	0x7F000000
#define	SMBCSR_WR_DATA_NACK	0x00040000
#define	SMBCSR_CMD_NACK		0x00020000
#define	SMBCSR_RELOAD		0x00010000
#define	SMBCSR_CMD_ADDR_MASK	0x0000FF00
#define	SMBCSR_SCL_STAT		0x00000080
#define	SMBCSR_SDA_STAT		0x00000040
#define	SMBCSR_EEPROM_PRESENT	0x00000020
#define	SMBCSR_INIT_LD_DONE	0x00000010
#define	SMBCSR_HW_BUSY_MASK	0x0000000F
#define	SMBCSR_HW_IDLE		0x00000000

/* SMB interface. */
#define	JME_SMBINTF		0x0444
#define	SMBINTF_RD_DATA_MASK	0xFF000000
#define	SMBINTF_RD_DATA_SHIFT	24
#define	SMBINTF_WR_DATA_MASK	0x00FF0000
#define	SMBINTF_WR_DATA_SHIFT	16
#define	SMBINTF_ADDR_MASK	0x0000FF00
#define	SMBINTF_ADDR_SHIFT	8
#define	SMBINTF_RD		0x00000020
#define	SMBINTF_WR		0x00000000
#define	SMBINTF_CMD_TRIGGER	0x00000010
#define	SMBINTF_BUSY		0x00000010
#define	SMBINTF_FAST_MODE	0x00000008
#define	SMBINTF_GPIO_SCL	0x00000004
#define	SMBINTF_GPIO_SDA	0x00000002
#define	SMBINTF_GPIO_ENB	0x00000001

#define	JME_EEPROM_SIG0		0x55
#define	JME_EEPROM_SIG1		0xAA
#define	JME_EEPROM_DESC_BYTES	3
#define	JME_EEPROM_DESC_END	0x80
#define	JME_EEPROM_FUNC_MASK	0x70
#define	JME_EEPROM_FUNC_SHIFT	4
#define	JME_EEPROM_PAGE_MASK	0x0F
#define	JME_EEPROM_PAGE_SHIFT	0

#define	JME_EEPROM_FUNC0	0
/* PCI configuration space. */
#define	JME_EEPROM_PAGE_BAR0	0
/* 128 bytes I/O window. */
#define	JME_EEPROM_PAGE_BAR1	1
/* 256 bytes I/O window. */
#define	JME_EEPROM_PAGE_BAR2	2

#define	JME_EEPROM_END		0xFF

#define	JME_EEPROM_MKDESC(f, p)						\
	((((f) & JME_EEPROM_FUNC_MASK) << JME_EEPROM_FUNC_SHIFT) |	\
	(((p) & JME_EEPROM_PAGE_MASK) << JME_EEPROM_PAGE_SHIFT))

/* 3-wire EEPROM interface. Obsolete interface, use SMBCSR. */
#define	JME_EEPINTF		0x0448
#define	EEPINTF_DATA_MASK	0xFFFF0000
#define	EEPINTF_DATA_SHIFT	16
#define	EEPINTF_ADDR_MASK	0x0000FC00
#define	EEPINTF_ADDR_SHIFT	10
#define	EEPRINTF_OP_MASK	0x00000300
#define	EEPINTF_OP_EXECUTE	0x00000080
#define	EEPINTF_DATA_OUT	0x00000008
#define	EEPINTF_DATA_IN		0x00000004
#define	EEPINTF_CLK		0x00000002
#define	EEPINTF_SEL		0x00000001

/* 3-wire EEPROM control and status. Obsolete interface, use SMBCSR. */
#define	JME_EEPCSR		0x044C
#define	EEPCSR_EEPROM_RELOAD	0x00000002
#define	EEPCSR_EEPROM_PRESENT	0x00000001

/* Misc registers. */
#define	JME_MISC_BASE_ADDR	0x800

/* Timer control and status. */
#define	JME_TMCSR		0x0800
#define	TMCSR_SW_INTR		0x80000000
#define	TMCSR_TIMER_INTR	0x10000000
#define	TMCSR_TIMER_ENB		0x01000000
#define	TMCSR_TIMER_COUNT_MASK	0x00FFFFFF

/* GPIO control and status. */
#define	JME_GPIO		0x0804
#define	GPIO_4_SPI_IN		0x80000000
#define	GPIO_3_SPI_IN		0x40000000
#define	GPIO_4_SPI_OUT		0x20000000
#define	GPIO_4_SPI_OUT_ENB	0x10000000
#define	GPIO_3_SPI_OUT		0x08000000
#define	GPIO_3_SPI_OUT_ENB	0x04000000
#define	GPIO_3_4_LED		0x00000000
#define	GPIO_3_4_GPIO		0x02000000
#define	GPIO_2_CLKREQN_IN	0x00100000
#define	GPIO_2_CLKREQN_OUT	0x00040000
#define	GPIO_2_CLKREQN_OUT_ENB	0x00020000
#define	GPIO_1_LED42_IN		0x00001000
#define	GPIO_1_LED42_OUT	0x00000400
#define	GPIO_1_LED42_OUT_ENB	0x00000200
#define	GPIO_1_LED42_ENB	0x00000100
#define	GPIO_0_SDA_IN		0x00000010
#define	GPIO_0_SDA_OUT		0x00000004
#define	GPIO_0_SDA_OUT_ENB	0x00000002
#define	GPIO_0_SDA_ENB		0x00000001

/* General purpose register 0. */
#define	JME_GPREG0		0x0808
#define	GPREG0_SH_POST_DW7_DIS	0x80000000
#define	GPREG0_SH_POST_DW6_DIS	0x40000000
#define	GPREG0_SH_POST_DW5_DIS	0x20000000
#define	GPREG0_SH_POST_DW4_DIS	0x10000000
#define	GPREG0_SH_POST_DW3_DIS	0x08000000
#define	GPREG0_SH_POST_DW2_DIS	0x04000000
#define	GPREG0_SH_POST_DW1_DIS	0x02000000
#define	GPREG0_SH_POST_DW0_DIS	0x01000000
#define	GPREG0_DMA_RD_REQ_8	0x00000000
#define	GPREG0_DMA_RD_REQ_6	0x00100000
#define	GPREG0_DMA_RD_REQ_5	0x00200000
#define	GPREG0_DMA_RD_REQ_4	0x00300000
#define	GPREG0_POST_DW0_ENB	0x00040000
#define	GPREG0_PCC_CLR_DIS	0x00020000
#define	GPREG0_FORCE_SCL_OUT	0x00010000
#define	GPREG0_DL_RSTB_DIS	0x00008000
#define	GPREG0_STICKY_RESET	0x00004000
#define	GPREG0_DL_RSTB_CFG_DIS	0x00002000
#define	GPREG0_LINK_CHG_POLL	0x00001000
#define	GPREG0_LINK_CHG_DIRECT	0x00000000
#define	GPREG0_MSI_GEN_SEL	0x00000800
#define	GPREG0_SMB_PAD_PU_DIS	0x00000400
#define	GPREG0_PCC_UNIT_16US	0x00000000
#define	GPREG0_PCC_UNIT_256US	0x00000100
#define	GPREG0_PCC_UNIT_US	0x00000200
#define	GPREG0_PCC_UNIT_MS	0x00000300
#define	GPREG0_PCC_UNIT_MASK	0x00000300
#define	GPREG0_INTR_EVENT_ENB	0x00000080
#define	GPREG0_PME_ENB		0x00000020
#define	GPREG0_PHY_ADDR_MASK	0x0000001F
#define	GPREG0_PHY_ADDR_SHIFT	0
#define	GPREG0_PHY_ADDR		1

/* General purpose register 1. */
#define	JME_GPREG1		0x080C
#define	GPREG1_RSS_IPV6_10_100	0x00000040	/* JMC250 A2 */
#define	GPREG1_HDPX_FIX		0x00000020	/* JMC250 A2 */
#define	GPREG1_INTDLY_UNIT_16US	0x00000018	/* JMC250 A1, A2 */
#define	GPREG1_INTDLY_UNIT_1US	0x00000010	/* JMC250 A1, A2 */
#define	GPREG1_INTDLY_UNIT_256NS	0x00000008	/* JMC250 A1, A2 */
#define	GPREG1_INTDLY_UNIT_16NS	0x00000000	/* JMC250 A1, A2 */
#define	GPREG1_INTDLY_MASK	0x00000007

/* MSIX entry number of interrupt source. */
#define	JME_MSINUM_BASE		0x0810
#define	JME_MSINUM_END		0x081F
#define	MSINUM_MASK		0x7FFFFFFF
#define	MSINUM_ENTRY_MASK	7
#define	MSINUM_REG_INDEX(x)	((x) / 8)
#define	MSINUM_INTR_SOURCE(x, y)	\
	(((x) & MSINUM_ENTRY_MASK) << (((y) & 7) * 4))
#define	MSINUM_NUM_INTR_SOURCE	32

/* Interrupt event status. */
#define	JME_INTR_STATUS		0x0820
#define	INTR_SW			0x80000000
#define	INTR_TIMER		0x40000000
#define	INTR_LINKCHG		0x20000000
#define	INTR_PAUSE		0x10000000
#define	INTR_MAGIC_PKT		0x08000000
#define	INTR_WAKEUP_PKT		0x04000000
#define	INTR_RXQ0_COAL_TO	0x02000000
#define	INTR_RXQ1_COAL_TO	0x01000000
#define	INTR_RXQ2_COAL_TO	0x00800000
#define	INTR_RXQ3_COAL_TO	0x00400000
#define	INTR_TXQ_COAL_TO	0x00200000
#define	INTR_RXQ0_COAL		0x00100000
#define	INTR_RXQ1_COAL		0x00080000
#define	INTR_RXQ2_COAL		0x00040000
#define	INTR_RXQ3_COAL		0x00020000
#define	INTR_TXQ_COAL		0x00010000
#define	INTR_RXQ3_DESC_EMPTY	0x00008000
#define	INTR_RXQ2_DESC_EMPTY	0x00004000
#define	INTR_RXQ1_DESC_EMPTY	0x00002000
#define	INTR_RXQ0_DESC_EMPTY	0x00001000
#define	INTR_RXQ3_COMP		0x00000800
#define	INTR_RXQ2_COMP		0x00000400
#define	INTR_RXQ1_COMP		0x00000200
#define	INTR_RXQ0_COMP		0x00000100
#define	INTR_TXQ7_COMP		0x00000080
#define	INTR_TXQ6_COMP		0x00000040
#define	INTR_TXQ5_COMP		0x00000020
#define	INTR_TXQ4_COMP		0x00000010
#define	INTR_TXQ3_COMP		0x00000008
#define	INTR_TXQ2_COMP		0x00000004
#define	INTR_TXQ1_COMP		0x00000002
#define	INTR_TXQ0_COMP		0x00000001

#define	INTR_RXQ_COAL_TO					\
	(INTR_RXQ0_COAL_TO | INTR_RXQ1_COAL_TO |		\
	 INTR_RXQ2_COAL_TO | INTR_RXQ3_COAL_TO)

#define	INTR_RXQ_COAL						\
	(INTR_RXQ0_COAL | INTR_RXQ1_COAL | INTR_RXQ2_COAL |	\
	 INTR_RXQ3_COAL)

#define	INTR_RXQ_COMP						\
	(INTR_RXQ0_COMP | INTR_RXQ1_COMP | INTR_RXQ2_COMP |	\
	 INTR_RXQ3_COMP)

#define	INTR_RXQ_DESC_EMPTY					\
	(INTR_RXQ0_DESC_EMPTY | INTR_RXQ1_DESC_EMPTY |		\
	INTR_RXQ2_DESC_EMPTY | INTR_RXQ3_DESC_EMPTY)

#define	INTR_RXQ_COMP						\
	(INTR_RXQ0_COMP | INTR_RXQ1_COMP | INTR_RXQ2_COMP |	\
	INTR_RXQ3_COMP)

#define	INTR_TXQ_COMP						\
	(INTR_TXQ0_COMP | INTR_TXQ1_COMP | INTR_TXQ2_COMP |	\
	INTR_TXQ3_COMP | INTR_TXQ4_COMP | INTR_TXQ5_COMP | 	\
	INTR_TXQ6_COMP | INTR_TXQ7_COMP)

#define	JME_INTRS						\
	(INTR_RXQ_COAL_TO | INTR_TXQ_COAL_TO | INTR_RXQ_COAL |	\
	 INTR_TXQ_COAL | INTR_RXQ_DESC_EMPTY)

#define	N_INTR_SW		31
#define	N_INTR_TIMER		30
#define	N_INTR_LINKCHG		29
#define	N_INTR_PAUSE		28
#define	N_INTR_MAGIC_PKT	27
#define	N_INTR_WAKEUP_PKT	26
#define	N_INTR_RXQ0_COAL_TO	25
#define	N_INTR_RXQ1_COAL_TO	24
#define	N_INTR_RXQ2_COAL_TO	23
#define	N_INTR_RXQ3_COAL_TO	22
#define	N_INTR_TXQ_COAL_TO	21
#define	N_INTR_RXQ0_COAL	20
#define	N_INTR_RXQ1_COAL	19
#define	N_INTR_RXQ2_COAL	18
#define	N_INTR_RXQ3_COAL	17
#define	N_INTR_TXQ_COAL		16
#define	N_INTR_RXQ3_DESC_EMPTY	15
#define	N_INTR_RXQ2_DESC_EMPTY	14
#define	N_INTR_RXQ1_DESC_EMPTY	13
#define	N_INTR_RXQ0_DESC_EMPTY	12
#define	N_INTR_RXQ3_COMP	11
#define	N_INTR_RXQ2_COMP	10
#define	N_INTR_RXQ1_COMP	9
#define	N_INTR_RXQ0_COMP	8
#define	N_INTR_TXQ7_COMP	7
#define	N_INTR_TXQ6_COMP	6
#define	N_INTR_TXQ5_COMP	5
#define	N_INTR_TXQ4_COMP	4
#define	N_INTR_TXQ3_COMP	3
#define	N_INTR_TXQ2_COMP	2
#define	N_INTR_TXQ1_COMP	1
#define	N_INTR_TXQ0_COMP	0

/* Interrupt request status. */
#define	JME_INTR_REQ_STATUS	0x0824

/* Interrupt enable - setting port. */
#define	JME_INTR_MASK_SET	0x0828

/* Interrupt enable - clearing port. */
#define	JME_INTR_MASK_CLR	0x082C

/* Packet completion coalescing control of Rx queue 0, 1, 2 and 3. */
#define	JME_PCCRX0		0x0830
#define	JME_PCCRX1		0x0834
#define	JME_PCCRX2		0x0838
#define	JME_PCCRX3		0x083C
#define	PCCRX_COAL_TO_MASK	0xFFFF0000
#define	PCCRX_COAL_TO_SHIFT	16
#define	PCCRX_COAL_PKT_MASK	0x0000FF00
#define	PCCRX_COAL_PKT_SHIFT	8

#define	PCCRX_COAL_TO_MIN	1
#define	PCCRX_COAL_TO_DEFAULT	100
#define	PCCRX_COAL_TO_MAX	65535

#define	PCCRX_COAL_PKT_MIN	1
#define	PCCRX_COAL_PKT_DEFAULT	2
#define	PCCRX_COAL_PKT_MAX	255

/* Packet completion coalescing control of Tx queue. */
#define	JME_PCCTX		0x0840
#define	PCCTX_COAL_TO_MASK	0xFFFF0000
#define	PCCTX_COAL_TO_SHIFT	16
#define	PCCTX_COAL_PKT_MASK	0x0000FF00
#define	PCCTX_COAL_PKT_SHIFT	8
#define	PCCTX_COAL_TXQ7		0x00000080
#define	PCCTX_COAL_TXQ6		0x00000040
#define	PCCTX_COAL_TXQ5		0x00000020
#define	PCCTX_COAL_TXQ4		0x00000010
#define	PCCTX_COAL_TXQ3		0x00000008
#define	PCCTX_COAL_TXQ2		0x00000004
#define	PCCTX_COAL_TXQ1		0x00000002
#define	PCCTX_COAL_TXQ0		0x00000001

#define	PCCTX_COAL_TO_MIN	1
#define	PCCTX_COAL_TO_DEFAULT	100
#define	PCCTX_COAL_TO_MAX	65535

#define	PCCTX_COAL_PKT_MIN	1
#define	PCCTX_COAL_PKT_DEFAULT	8
#define	PCCTX_COAL_PKT_MAX	255

/* Chip mode and FPGA version. */
#define	JME_CHIPMODE		0x0844
#define	CHIPMODE_FPGA_REV_MASK	0xFFFF0000
#define	CHIPMODE_FPGA_REV_SHIFT	16
#define	CHIPMODE_NOT_FPGA	0
#define	CHIPMODE_REV_MASK	0x0000FF00
#define	CHIPMODE_REV_SHIFT	8
#define	CHIPMODE_MODE_48P	0x0000000C
#define	CHIPMODE_MODE_64P	0x00000004
#define	CHIPMODE_MODE_128P_MAC	0x00000003
#define	CHIPMODE_MODE_128P_DBG	0x00000002
#define	CHIPMODE_MODE_128P_PHY	0x00000000
/* Chip full mask revision. */
#define	CHIPMODE_REVFM(x)	((x) & 0x0F)
/* Chip ECO revision. */
#define	CHIPMODE_REVECO(x)	(((x) >> 4) & 0x0F)

/* Shadow status base address high/low. */
#define	JME_SHBASE_ADDR_HI	0x0848
#define	JME_SHBASE_ADDR_LO	0x084C
#define	SHBASE_ADDR_LO_MASK	0xFFFFFFE0
#define	SHBASE_POST_FORCE	0x00000002
#define	SHBASE_POST_ENB		0x00000001

/* Timer 1 and 2. */
#define	JME_TIMER1		0x0870
#define	JME_TIMER2		0x0874
#define	TIMER_ENB		0x01000000
#define	TIMER_CNT_MASK		0x00FFFFFF
#define	TIMER_CNT_SHIFT		0
#define	TIMER_UNIT		1024	/* 1024us */

/* Aggresive power mode control. */
#define	JME_APMC		0x087C
#define	APMC_PCIE_SDOWN_STAT	0x80000000
#define	APMC_PCIE_SDOWN_ENB	0x40000000
#define	APMC_PSEUDO_HOT_PLUG	0x20000000
#define	APMC_EXT_PLUGIN_ENB	0x04000000
#define	APMC_EXT_PLUGIN_CTL_MSK	0x03000000
#define	APMC_DIS_SRAM		0x00000004
#define	APMC_DIS_CLKPM		0x00000002
#define	APMC_DIS_CLKTX		0x00000001

/* Packet completion coalesing status of Rx queue 0, 1, 2 and 3. */
#define	JME_PCCSRX_BASE		0x0880
#define	JME_PCCSRX_END		0x088F
#define	PCCSRX_REG(x)		(JME_PCCSRX_BASE + ((x) * 4))
#define	PCCSRX_TO_MASK		0xFFFF0000
#define	PCCSRX_TO_SHIFT		16
#define	PCCSRX_PKT_CNT_MASK	0x0000FF00
#define	PCCSRX_PKT_CNT_SHIFT	8

/* Packet completion coalesing status of Tx queue. */
#define	JME_PCCSTX		0x0890
#define	PCCSTX_TO_MASK		0xFFFF0000
#define	PCCSTX_TO_SHIFT		16
#define	PCCSTX_PKT_CNT_MASK	0x0000FF00
#define	PCCSTX_PKT_CNT_SHIFT	8

/* Tx queues empty indicator. */
#define	JME_TXQEMPTY		0x0894
#define	TXQEMPTY_TXQ7		0x00000080
#define	TXQEMPTY_TXQ6		0x00000040
#define	TXQEMPTY_TXQ5		0x00000020
#define	TXQEMPTY_TXQ4		0x00000010
#define	TXQEMPTY_TXQ3		0x00000008
#define	TXQEMPTY_TXQ2		0x00000004
#define	TXQEMPTY_TXQ1		0x00000002
#define	TXQEMPTY_TXQ0		0x00000001
#define	TXQEMPTY_N_TXQ(x, y)	((x) & (0x01 << (y)))

/* RSS control registers. */
#define	JME_RSS_BASE		0x0C00

#define	JME_RSSC		0x0C00
#define	RSSC_HASH_LEN_MASK	0x0000E000
#define	RSSC_HASH_64_ENTRY	0x0000A000
#define	RSSC_HASH_128_ENTRY	0x0000E000
#define	RSSC_HASH_NONE		0x00001000
#define	RSSC_HASH_IPV6		0x00000800
#define	RSSC_HASH_IPV4		0x00000400
#define	RSSC_HASH_IPV6_TCP	0x00000200
#define	RSSC_HASH_IPV4_TCP	0x00000100
#define	RSSC_NCPU_MASK		0x000000F8
#define	RSSC_NCPU_SHIFT		3
#define	RSSC_DIS_RSS		0x00000000
#define	RSSC_2RXQ_ENB		0x00000001
#define	RSSS_4RXQ_ENB		0x00000002

/* CPU vector. */
#define	JME_RSSCPU		0x0C04
#define	RSSCPU_N_SEL(x)		((1 << (x))

/* RSS Hash value. */
#define	JME_RSSHASH		0x0C10

#define	JME_RSSHASH_STAT	0x0C14

#define	JME_RSS_RDATA0		0x0C18

#define	JME_RSS_RDATA1		0x0C1C

/* RSS secret key. */
#define	JME_RSSKEY_BASE		0x0C40
#define	JME_RSSKEY_LAST		0x0C64
#define	JME_RSSKEY_END		0x0C67
#define	HASHKEY_NBYTES		40
#define	RSSKEY_REG(x)		(JME_RSSKEY_LAST - (4 * ((x) / 4)))
#define	RSSKEY_VALUE(x, y)	((x) << (24 - 8 * ((y) % 4)))

/* RSS indirection table entries. */
#define	JME_RSSTBL_BASE		0x0C80
#define	JME_RSSTBL_END		0x0CFF
#define	RSSTBL_NENTRY		128
#define	RSSTBL_REG(x)		(JME_RSSTBL_BASE + ((x) / 4))
#define	RSSTBL_VALUE(x, y)	((x) << (8 * ((y) % 4)))

/* MSI-X table. */
#define	JME_MSIX_BASE_ADDR	0x2000

#define	JME_MSIX_BASE		0x2000
#define	JME_MSIX_END		0x207F
#define	JME_MSIX_NENTRY		8
#define	MSIX_REG(x)		(JME_MSIX_BASE + ((x) * 0x10))
#define	MSIX_ADDR_HI_OFF	0x00
#define	MSIX_ADDR_LO_OFF	0x04
#define	MSIX_ADDR_LO_MASK	0xFFFFFFFC
#define	MSIX_DATA_OFF		0x08
#define	MSIX_VECTOR_OFF		0x0C
#define	MSIX_VECTOR_RSVD	0x80000000
#define	MSIX_VECTOR_DIS		0x00000001

/* MSI-X PBA. */
#define	JME_MSIX_PBA_BASE_ADDR	0x3000

#define	JME_MSIX_PBA		0x3000
#define	MSIX_PBA_RSVD_MASK	0xFFFFFF00
#define	MSIX_PBA_RSVD_SHIFT	8
#define	MSIX_PBA_PEND_MASK	0x000000FF
#define	MSIX_PBA_PEND_SHIFT	0
#define	MSIX_PBA_PEND_ENTRY7	0x00000080
#define	MSIX_PBA_PEND_ENTRY6	0x00000040
#define	MSIX_PBA_PEND_ENTRY5	0x00000020
#define	MSIX_PBA_PEND_ENTRY4	0x00000010
#define	MSIX_PBA_PEND_ENTRY3	0x00000008
#define	MSIX_PBA_PEND_ENTRY2	0x00000004
#define	MSIX_PBA_PEND_ENTRY1	0x00000002
#define	MSIX_PBA_PEND_ENTRY0	0x00000001

#define	JME_PHY_OUI		0x001B8C
#define	JME_PHY_MODEL		0x21
#define	JME_PHY_REV		0x01
#define	JME_PHY_ADDR		1

/* JMC250 shadow status block. */
struct jme_ssb {
	uint32_t	dw0;
	uint32_t	dw1;
	uint32_t	dw2;
	uint32_t	dw3;
	uint32_t	dw4;
	uint32_t	dw5;
	uint32_t	dw6;
	uint32_t	dw7;
};

/* JMC250 descriptor structures. */
struct jme_desc {
	uint32_t	flags;
	uint32_t	buflen;
	uint32_t	addr_hi;
	uint32_t	addr_lo;
};

#define	JME_TD_OWN		0x80000000
#define	JME_TD_INTR		0x40000000
#define	JME_TD_64BIT		0x20000000
#define	JME_TD_TCPCSUM		0x10000000
#define	JME_TD_UDPCSUM		0x08000000
#define	JME_TD_IPCSUM		0x04000000
#define	JME_TD_TSO		0x02000000
#define	JME_TD_VLAN_TAG		0x01000000
#define	JME_TD_VLAN_MASK	0x0000FFFF

#define	JME_TD_MSS_MASK		0xFFFC0000
#define	JME_TD_MSS_SHIFT	18
#define	JME_TD_BUF_LEN_MASK	0x0000FFFF
#define	JME_TD_BUF_LEN_SHIFT	0

#define	JME_TD_FRAME_LEN_MASK	0x0000FFFF
#define	JME_TD_FRAME_LEN_SHIFT	0

/*
 * Only the first Tx descriptor of a packet is updated
 * after packet transmission.
 */
#define	JME_TD_TMOUT		0x20000000
#define	JME_TD_RETRY_EXP	0x10000000
#define	JME_TD_COLLISION	0x08000000
#define	JME_TD_UNDERRUN		0x04000000
#define	JME_TD_EHDR_SIZE_MASK	0x000000FF
#define	JME_TD_EHDR_SIZE_SHIFT	0

#define	JME_TD_SEG_CNT_MASK	0xFFFF0000
#define	JME_TD_SEG_CNT_SHIFT	16
#define	JME_TD_RETRY_CNT_MASK	0x0000FFFF
#define	JME_TD_RETRY_CNT_SHIFT	0

#define	JME_RD_OWN		0x80000000
#define	JME_RD_INTR		0x40000000
#define	JME_RD_64BIT		0x20000000

#define	JME_RD_BUF_LEN_MASK	0x0000FFFF
#define	JME_RD_BUF_LEN_SHIFT	0

/*
 * Only the first Rx descriptor of a packet is updated
 * after packet reception.
 */
#define	JME_RD_MORE_FRAG	0x20000000
#define	JME_RD_TCP		0x10000000
#define	JME_RD_UDP		0x08000000
#define	JME_RD_IPCSUM		0x04000000
#define	JME_RD_TCPCSUM		0x02000000
#define	JME_RD_UDPCSUM		0x01000000
#define	JME_RD_VLAN_TAG		0x00800000
#define	JME_RD_IPV4		0x00400000
#define	JME_RD_IPV6		0x00200000
#define	JME_RD_PAUSE		0x00100000
#define	JME_RD_MAGIC		0x00080000
#define	JME_RD_WAKEUP		0x00040000
#define	JME_RD_BCAST		0x00030000
#define	JME_RD_MCAST		0x00020000
#define	JME_RD_UCAST		0x00010000
#define	JME_RD_VLAN_MASK	0x0000FFFF
#define	JME_RD_VLAN_SHIFT	0

#define	JME_RD_VALID		0x80000000
#define	JME_RD_CNT_MASK		0x7F000000
#define	JME_RD_CNT_SHIFT	24
#define	JME_RD_GIANT		0x00800000
#define	JME_RD_GMII_ERR		0x00400000
#define	JME_RD_NBL_RCVD		0x00200000
#define	JME_RD_COLL		0x00100000
#define	JME_RD_ABORT		0x00080000
#define	JME_RD_RUNT		0x00040000
#define	JME_RD_FIFO_OVRN	0x00020000
#define	JME_RD_CRC_ERR		0x00010000
#define	JME_RD_FRAME_LEN_MASK	0x0000FFFF

#define	JME_RX_ERR_STAT						\
	(JME_RD_GIANT | JME_RD_GMII_ERR | JME_RD_NBL_RCVD |	\
	JME_RD_COLL | JME_RD_ABORT | JME_RD_RUNT |		\
	JME_RD_FIFO_OVRN | JME_RD_CRC_ERR)

#define	JME_RD_ERR_MASK		0x00FF0000
#define	JME_RD_ERR_SHIFT	16
#define	JME_RX_ERR(x)		(((x) & JME_RD_ERR_MASK) >> JME_RD_ERR_SHIFT)
#define	JME_RX_ERR_BITS		"\20"					\
				"\1CRCERR\2FIFOOVRN\3RUNT\4ABORT"	\
				"\5COLL\6NBLRCVD\7GMIIERR\10"

#define	JME_RX_NSEGS(x)		(((x) & JME_RD_CNT_MASK) >> JME_RD_CNT_SHIFT)
#define	JME_RX_BYTES(x)		((x) & JME_RD_FRAME_LEN_MASK)
#define	JME_RX_PAD_BYTES	10

#define	JME_RD_RSS_HASH_VALUE	0xFFFFFFFF

#define	JME_RD_RSS_HASH_MASK	0x00003F00
#define	JME_RD_RSS_HASH_SHIFT	8
#define	JME_RD_RSS_HASH_NONE	0x00000000
#define	JME_RD_RSS_HASH_IPV4	0x00000100
#define	JME_RD_RSS_HASH_IPV4TCP	0x00000200
#define	JME_RD_RSS_HASH_IPV6	0x00000400
#define	JME_RD_RSS_HASH_IPV6TCP	0x00001000
#define	JME_RD_HASH_FN_NONE	0x00000000
#define	JME_RD_HASH_FN_TOEPLITZ	0x00000001

#endif
