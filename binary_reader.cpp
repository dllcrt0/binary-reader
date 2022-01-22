#include "binary_reader.h"
#include <stack>

namespace io {
    float binary_reader::read_float() {
        if (is_valid(sizeof(float))) {
            float value = *(float*)&m_raw[m_index];
            m_index += sizeof(float);
            return value;
        }

        return 0.0f;
    }

    double binary_reader::read_double() {
        if (is_valid(sizeof(double))) {
            double value = *(double*)&m_raw[m_index];
            m_index += sizeof(double);
            return value;
        }

        return 0.0;
    }

    short binary_reader::read_int16() {
        if (is_valid(sizeof(short))) {
            short value = *(short*)&m_raw[m_index];
            m_index += sizeof(short);
            return value;
        }

        return 0;
    }

    uint16_t binary_reader::read_uint16() {
        if (is_valid(sizeof(uint16_t))) {
            uint16_t value = *(uint16_t*)&m_raw[m_index];
            m_index += sizeof(uint16_t);
            return value;
        }

        return 0;
    }

    int binary_reader::read_int24() {
        if (is_valid(3)) {
            uint8_t* buffer = alloc(3);
            memcpy(buffer, (m_raw + m_index), 3);

            m_index += 3;
            return (((buffer[2] << 0x10) | (buffer[1] << 8)) | buffer[0]);
        }

        return 0;
    }

    int binary_reader::read_int32() {
        if (is_valid(sizeof(int))) {
            int value = *(int*)&m_raw[m_index];
            m_index += sizeof(int);
            return value;
        }

        return 0;
    }

    uint32_t binary_reader::read_uint32() {
        if (is_valid(sizeof(uint32_t))) {
            uint32_t value = *(uint32_t*)&m_raw[m_index];
            m_index += sizeof(uint32_t);
            return value;
        }

        return 0;
    }

    int64_t binary_reader::read_int64() {
        if (is_valid(sizeof(int64_t))) {
            int64_t value = *(int64_t*)&m_raw[m_index];
            m_index += sizeof(int64_t);
            return value;
        }

        return 0;
    }

    uint64_t binary_reader::read_uint64() {
        if (is_valid(sizeof(uint64_t))) {
            uint64_t value = *(uint64_t*)&m_raw[m_index];
            m_index += sizeof(uint64_t);
            return value;
        }

        return 0;
    }

    char binary_reader::read_byte() {
        if (is_valid(sizeof(char))) {
            char value = *(char*)&m_raw[m_index];
            m_index += sizeof(char);
            return value;
        }

        return 0;
    }

    uint8_t binary_reader::read_ubyte() {
        if (is_valid(sizeof(uint8_t))) {
            uint8_t value = *(uint8_t*)&m_raw[m_index];
            m_index += sizeof(uint8_t);
            return value;
        }

        return 0;
    }

    bool binary_reader::read_bool() {
        if (is_valid(sizeof(bool))) {
            bool value = *(bool*)&m_raw[m_index];
            m_index += sizeof(bool);
            return value;
        }

        return false;
    }

    const char* binary_reader::read_string(uint32_t size) {
        if (is_valid(size)) {
            char* buffer = (char*)alloc(size + 1);
            memcpy(buffer, (m_raw + m_index), size);

            m_index += size;
            return (const char*)buffer;
        }

        return NULL;
    }

    uint8_t* binary_reader::read_bytes(uint32_t size) {
        if (is_valid(size)) {
            uint8_t* buffer = alloc(size);
            memcpy(buffer, (m_raw + m_index), size);

            m_index += size;
            return buffer;
        }

        return nullptr;
    }

    void binary_reader::copy(uint8_t* destination, uint32_t size) {
        uint8_t* buffer = read_bytes(size);
        if (buffer)
            memcpy(destination, buffer, size);
    }

    void binary_reader::release() {
        for (uint8_t* memory : m_memory)
            free(memory);
    }

    uint8_t* binary_reader::alloc(uint32_t size) {
        uint8_t* memory = (uint8_t*)malloc(size);
        if (!memory)
            return nullptr;

        m_memory.push_back(memory);

        memset(memory, 0, size);
        return memory;
    }

    bool binary_reader::is_valid(uint32_t size) {
        return !((m_index + size) > m_size);
    }


    void binary_reader::advance(uint32_t bytes) {
        if (is_valid(bytes))
            m_index += bytes;
    }

    void binary_reader::reverse(uint8_t* buffer, uint32_t size) {
        // found this function online a long time ago, not sure where
        std::stack<uint8_t> stack;
        for (uint32_t i = 0; i < size; i++)
            stack.push(buffer[i]);

        int index = 0;
        while (!stack.empty()) {
            buffer[index++] = stack.top();
            stack.pop();
        }
    }
}