/**
 * Functions like isupper can be implemented to save space or to
 * save time. Explore both possibilities.
 */

/**
 * saves time, as a macro, but wastes space in source code since the corresponding
 * text is expanded
 */
#define isupper_time(c) ((c) >= 'A' && (c) <= 'Z')

/**
 * saves space in source code, but requires function call
 */
int isupper_space(char c) {
    return c >= 'A' && c <= 'Z';
}