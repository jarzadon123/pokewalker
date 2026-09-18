#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Standard Pokewalker Packet Structure (10-byte header frame)
typedef struct {
    uint8_t  command;
    uint8_t  sub_command;
    uint32_t session_id;
    uint16_t checksum;
    uint16_t payload_len;
} __attribute__((packed)) pokewalker_header_t;

/**
 * @brief Pokewalker custom 16-bit checksum algorithm.
 * Operates on the de-obfuscated bytes excluding the checksum field itself.
 */
uint16_t calculate_pokewalker_checksum(const uint8_t *buffer, size_t length) {
    uint32_t sum = 0;
    for (size_t i = 0; i < length; i++) {
        // Skip the two checksum bytes located at index 6 and 7 in the frame header
        if (i == 6 || i == 7) continue; 
        sum += buffer[i];
    }
    return (uint16_t)(sum & 0xFFFF);
}

/**
 * @brief De-obfuscates raw IR bytes by XORing each with 0xAA in-place.
 */
void deobfuscate_buffer(uint8_t *buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        buffer[i] ^= 0xAA;
    }
}

/**
 * @brief Parses and validates an incoming raw Pokewalker packet buffer.
 */
bool parse_pokewalker_packet(uint8_t *raw_buf, size_t len) {
    if (len < sizeof(pokewalker_header_t)) {
        printf("[ERROR] Packet length (%zu) too short for header.\n", len);
        return false;
    }

    // 1. De-obfuscate raw byte stream in-place
    deobfuscate_buffer(raw_buf, len);

    // 2. Extract header fields (Little-Endian layout)
    pokewalker_header_t header;
    header.command     = raw_buf[0];
    header.sub_command = raw_buf[1];
    header.session_id  = (uint32_t)raw_buf[2] | ((uint32_t)raw_buf[3] << 8) | 
                         ((uint32_t)raw_buf[4] << 16) | ((uint32_t)raw_buf[5] << 24);
    header.checksum    = (uint16_t)raw_buf[6] | ((uint16_t)raw_buf[7] << 8);
    header.payload_len = (uint16_t)raw_buf[8] | ((uint16_t)raw_buf[9] << 8);

    // 3. Verify total packet length matches expected header declaration
    size_t expected_total_len = sizeof(pokewalker_header_t) + header.payload_len;
    if (len < expected_total_len) {
        printf("[ERROR] Incomplete payload. Expected: %zu bytes, Got: %zu bytes\n", 
               expected_total_len, len);
        return false;
    }

    // 4. Validate Checksum
    uint16_t calculated_crc = calculate_pokewalker_checksum(raw_buf, expected_total_len);
    bool checksum_valid = (calculated_crc == header.checksum);

    // 5. Print Detailed Output
    printf("--- PARSED POKEWALKER PACKET ---\n");
    printf("Command ID     : 0x%02X\n", header.command);
    printf("Sub-Command    : 0x%02X\n", header.sub_command);
    printf("Session ID     : 0x%08X\n", header.session_id);
    printf("Payload Length : %u bytes\n", header.payload_len);
    printf("Header Checksum: 0x%04X\n", header.checksum);
    printf("Calculated CRC : 0x%04X\n", calculated_crc);
    printf("Status         : %s\n", checksum_valid ? "VALID (PASS)" : "INVALID (FAIL)");
    printf("--------------------------------\n");

    return checksum_valid;
}

int main(void) {
    // Simulated raw byte stream captured over IrDA (XOR-obfuscated with 0xAA)
    // Command 0x30, Sub 0x01, Session ID 0x12345678, Checksum 0x0211, Payload Length 0x0002
    uint8_t test_raw_packet[] = {
        0x9A, 0xAB,                   // Obfuscated Cmd (0x30), SubCmd (0x01)
        0xD2, 0x9E, 0x9E, 0xB8,       // Obfuscated Session ID (0x12345678)
        0xBB, 0xA8,                   // Obfuscated Checksum (0x0211)
        0xA8, 0xAA,                   // Obfuscated Payload Len (0x0002)
        0xDE, 0xAD                    // Obfuscated Payload Data
    };

    size_t packet_size = sizeof(test_raw_packet);

    printf("Processing %zu-byte raw IR packet...\n\n", packet_size);
    parse_pokewalker_packet(test_raw_packet, packet_size);

    return 0;
}