#include "assembler.h"

/*lengt of the bites of each place in the word*/
enum length {
    OPCODE_LEN = 6, AddressingSource_LEN = 2, SourceRegister_LEN = 3, AddressingDestination_LEN = 2,
    TargetRegister_LEN = 3, FUNCT_LEN = 5, ARE_LEN = 3, VAL_LEN = 21, VAL_ALL = 24
};

/*the first bit of each place in the word*/
enum firstBit {
    OPCODE_FIRST_BIT = 18, ADD_SOURCE_FIRST_BIT = 16, SOURCE_REGISTER_FIRST_BIT = 13, ADD_DESTINATION_FIRST_BIT = 11,
    TARGET_REGISTER_FIRST_BIT = 8, FUNC_FIRST_BIT = 3, ARE_FIRST_BIT = 0, VAL_FIRST_BIT = 3
};

/*set the word - calculating all the bits together
 * @param w - param to the new label we want to copy to
 * @param num -the old label we copy from.
 * @param firstBit - the first bit of the place we want to enter the number
 * @param length - representing the length of the bites
*/
void set(word *w, int num, int firstBit, int length) {
    /* Using bitwise operations to change the specific bits */
    w->val &= ~(((1 << length) - 1) << firstBit);
    w->val += num * (1 << firstBit);
}

/*Will set the Opcode of the word
 * @param w - param to the new label we want to copy to
 * @param num - the num we want to put in the word
*/
void setOpcode(word *w, int num) {

    set(w, num, OPCODE_FIRST_BIT, OPCODE_LEN);
}

/*Will set the addressing source of the word
 * @param w - param to the new label we want to copy to
 * @param num - the num we want to put in the word
*/
void setAddressingSource(word *w, int num) {
    set(w, num, ADD_SOURCE_FIRST_BIT, AddressingSource_LEN);
}

/*Will set the source register of the word
 * @param w - param to the new label we want to copy to
 * @param num - the num we want to put in the word
*/
void setSourceRegister(word *w, int num) {
    set(w, num, SOURCE_REGISTER_FIRST_BIT, SourceRegister_LEN);
}

/*Will set the addressing destination of the word
 * @param w - param to the new label we want to copy to
 * @param num - the num we want to put in the word
*/
void setAddressingDestination(word *w, int num) {
    set(w, num, ADD_DESTINATION_FIRST_BIT, AddressingDestination_LEN);
}

/*Will set the target register of the word
 * @param w - param to the new label we want to copy to
 * @param num - the num we want to put in the word
*/
void setTargetRegister(word *w, int num) {
    set(w, num, TARGET_REGISTER_FIRST_BIT, TargetRegister_LEN);
}

/*Will set the function of the word
 * @param w - param to the new label we want to copy to
 * @param num - the num we want to put in the word
*/
void SetFunct(word *w, int num) {
    set(w, num, FUNC_FIRST_BIT, FUNCT_LEN);
}

/*Will set the ARE of the word
 * @param w - param to the new label we want to copy to
 * @param num - the num we want to put in the word
*/
void setARE(word *w, int num) {
    set(w, num, ARE_FIRST_BIT, ARE_LEN);
}

/*Will set the value of the word
 * @param w - param to the new label we want to copy to
 * @param num - the num we want to put in the word
*/
void setValue(word *w, int num) {
    set(w, num, VAL_FIRST_BIT, VAL_LEN);
}

/*Will set the full number in the word
 * @param w - param to the new label we want to copy to
 * @param num - the num we want to put in the word
*/
void setNum(word *w, int num) {
    set(w, num, ARE_FIRST_BIT, VAL_ALL);
}