# Regression test for Rule 17.3 false positives with #if-duplicated
# typedefs (generated ADAS/RTE type headers pattern).
#
# The type header provides two variants of the same type behind
# preprocessor conditions.  cppcheck analyses one configuration per
# variant; in the enum variant the symbol database loses the function
# link on prototype/definition/call tokens of adapter functions.
# Rule 17.3 must NOT be reported for these calls (declaration is
# visible in the translation unit in another configuration).
# Expected: no misra-c2012-17.3

typedef enum {
    LSS_TUNINGMODE_NOT_REQUESTED = 0,
    LSS_TUNINGMODE_REQUESTED = 1
} AdapterT;

#ifdef USE_INT_TYPE
typedef unsigned int AdapterT;
#endif

AdapterT LssTuningModeAdapter(int mode);

AdapterT LssTuningModeAdapter(int mode)
{
    AdapterT result;
    result = (0 == mode) ? LSS_TUNINGMODE_NOT_REQUESTED : LSS_TUNINGMODE_REQUESTED;
    return result;
}

int use_adapter(int mode)
{
    /* call with visible prototype — must not be 17.3 */
    AdapterT adapted = LssTuningModeAdapter(mode);
    return (int)adapted;
}

/* genuinely implicit call — must stay 17.3 */
int implicit_caller(void)
{
    return never_declared_function(1); // 17.3
}
