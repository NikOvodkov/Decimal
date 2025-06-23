/**
 * @brief Сдвигает мантиссу вправо на указанное количество бит.
 *
 * @param value Указатель на s21_decimal.
 * @param shift Количество бит для сдвига (от 1 до 32).
 * @return int 1 — потеря данных (ненулевые биты утеряны), 0 — успех.
 */
int s21_shift_right(s21_decimal *value, int shift) {
    uint64_t carry = 0;
    int underflow = 0;
    if (shift < 1 || shift > 32)
        underflow = 1;
    else
        for (int i = 2; i >= 0; i--) {
            uint64_t current = (uint64_t)value->bits[i];
            uint64_t shifted = (current >> shift) | carry;
            carry = (current & ((1ULL << shift) - 1)) << (32 - shift);

            value->bits[i] = (int)shifted;

            // Если при последнем шаге мы теряем ненулевые биты — это underflow
            if (i == 0 && carry != 0) underflow = 1;
        }

    return underflow;
}

/**
 * @brief Сдвигает мантиссу влево на указанное количество бит.
 *
 * @param value Указатель на s21_decimal.
 * @param shift Количество бит для сдвига (от 1 до 32).
 * @return int 1 — переполнение, 0 — успех.
 */
int s21_shift_left(s21_decimal *value, int shift) {
    if (shift < 1 || shift > 32) return 1;

    uint64_t carry = 0;
    for (int i = 0; i < 3; i++) {
        uint64_t current = (uint64_t)value->bits[i];
        uint64_t shifted = (current << shift) | carry;
        value->bits[i] = (int)(shifted & 0xFFFFFFFF); // Сохраняем младшие 32 бита
        carry = shifted >> 32;                        // Переносим старшие биты
    }

    // Проверяем, есть ли остаток в carry — это переполнение
    if (carry != 0) return 1;

    return 0;
}