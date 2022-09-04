#include <stdio.h>
#include <string.h>

#include "crc.h"
#include "arp.h"
#include "enc28j60.h"
#include "enc28j60_config.h"

bool compare_array(uint8_t* a,const uint8_t* b, uint8_t len){
	uint8_t i = 0;
	for (i=0;i<len;i++){
		if(a[i] != b[i]){
			return false;
		}
	}
	return true;
}

void arp_send_packet(uint8_t* package, uint16_t len){
	enc28j60_send_packet(package, ARP_PACKET_LEN);
}

extern bool arp_receiver_package(uint8_t* mac){
	static uint8_t arp_data[100];
	static uint16_t arp_length = 0;
	arp_length = enc28j60_receive_package(arp_data);
	if (arp_length > 0){
		/* compare opcode */
		if((arp_data[ARP_I_OPCODE]*256 +arp_data[ARP_I_OPCODE+1])  == ARP_OPCODE_REQUEST){
			/* compare MAC source */
			if(compare_array(&arp_data[ARP_I_MAC_TARGET], _MAC_SOURCE, 6)){
				if(compare_array(&arp_data[ARP_I_IP_TARGET], _IP_SOURCE, 4)){
					memcpy(mac, &arp_data[ARP_I_MAC_SENDER], 6);
					#ifdef DEBUG_ARP
						printf("MAC: %02x %02x %02x %02x %02x %02x\r\n",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
					#endif
					return true;
				}
			}
		}
	}
	return false;
}

extern bool arp_get_mac(uint8_t* mac_target,const uint8_t* ip_target){
	uint16_t status;
	int16_t timeout = 1000;
	uint8_t mac_dest[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	ARP_Struct arp_struct;
	
	enc28j60_init(_MAC_SOURCE);

	memcpy(arp_struct.MAC_dest, mac_dest, 6);
	memcpy(arp_struct.MAC_source, _MAC_SOURCE, 6);
	
	arp_struct.Ethernet_type = swap16(ARP_ETHERNET_TYPE);
	arp_struct.Hardwave_type = swap16(ARP_HARDWAVE_TYPE);
	arp_struct.Protocol_type = swap16(ARP_PROTOCOL_TYPE);
	arp_struct.Size = swap16(ARP_SIZE);
	arp_struct.Opcode = swap16(ARP_OPCODE_REPLY);
	
	memcpy(arp_struct.MAC_sender, _MAC_SOURCE, 6);
	memcpy(arp_struct.IP_sender, _IP_SOURCE, 4);
	memcpy(arp_struct.MAC_target, mac_target, 6);
	memcpy(arp_struct.IP_target, ip_target, 4);

	while(timeout--){
		arp_send_packet((uint8_t *)&arp_struct, ARP_PACKET_LEN);
		delay_ms(50);
		status = arp_receiver_package(mac_target);
		if (status == true){
			break;
		}
	}
	if(timeout >= 0){
		enc28j60_write_control_res(BANK_0, ERDPTL, 0);
		enc28j60_write_control_res(BANK_0, ERDPTH, 0);
		return true;
	}
	return false;
}

