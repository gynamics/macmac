/*
 * MACMAC: MAGIC C MACROS
 *
 * This header includes some interesting macros, most of them are inspired
 * from LISP functions, however, it is not a LISP emulation, most recursive
 * operations depends on a macro which expand other macros by hand.
 * ENJOY:)
 */
#ifndef __MAGIC_C_MACROS_H__
#define __MAGIC_C_MACROS_H__

// empty, it does not have actual value
#define _V
#define _E()
#define _T(...)    1
#define _NIL(...)  ()
#define _I(...) __VA_ARGS__
#define t _T()
#define nil _NIL()

/* 
 * car: get the first element in the list 
 * if the list is empty, return nil 
 */
#define _CAR_AT(arg0, arg1, ...) arg1 
#define _CAR(...) _CAR_AT(nil, ##__VA_ARGS__, nil) 
#define car(l) _CAR l

/* 
 * cdr: get a list with the first element deleted
 * if there are no more than 1 elements in the list, return nil
 */
#define _CDR_AT(arg1, ...) (__VA_ARGS__) 
#define _CDR(arg1, ...) _CDR_AT(_V, ##__VA_ARGS__)
#define cdr(l) _CDR l

/*
 * atom: decide whether an element is of atom type
 * lists and nil are not of atom type, return nil
 * otherwise, return t
 */
// COmma, if ... is empty, the comma will disappear
#define _ATOM_CO(...) , ##__VA_ARGS__
// Delay Evaluation, but only in one step
#define _ATOM_DE(f, ...) f(__VA_ARGS__)
// Eat Comma, produces _V or _V, a
#define _ATOM_EC(a, ...) _V _ATOM_CO(a)
#define _ATOM_AT(arg0, arg1, arg2, arg3, ...) arg3
#define _ATOM(...) _ATOM_AT(_V, ##__VA_ARGS__, nil, t, nil)
#define atom(l) _ATOM_DE(_ATOM, _ATOM_EC l)

/*
 * apply: apply a function to a list
 * it is extremely easy but still useful
 * almost each function implements it locally
 */
#define _APPLY_CO(...) , ##__VA_ARGS__
#define _APPLY_DE(f, ...) f(__VA_ARGS__)
#define _APPLY_DE2(f, ...) f(__VA_ARGS__)
#define _APPLY(f, ...) f(__VA_ARGS__)
#define apply(f, l) _APPLY_DE2(_APPLY_DE, f _APPLY_CO l)

/*
 * cons: construct a new list by combing its first argument
 * and all elements in the second argument.
 */
#define _CONS_CO(...) , ##__VA_ARGS__
#define cons(a, l) (a _CONS_CO l)

/*
 * append1: combine two lists into one list
 */
#define _APD1_AT(v, ...) ( __VA_ARGS__ )
#define _APD1_CO(...) , ##__VA_ARGS__
#define _APD1_DE(f, ...) f(__VA_ARGS__)
#define _APD1_DE2(f, ...) f(__VA_ARGS__)
#define _APPEND1(l1, l2) _APD1_DE2(_APD1_AT, _APD1_DE(_APD1_CO, _I l1) _APD1_DE(_APD1_CO, _I l2))
#define append1(l1, l2) _APPEND1(l1, l2)

/*
 * mif: simple conditional judgement
 * to distinguish from keyword if
 */
#define _MIF_CO(...) , ##__VA_ARGS__
#define _MIF_DE(f, ...) f(__VA_ARGS__)
#define _MIF_DE2(f, ...) f(__VA_ARGS__)
#define _MIF_AT(arg0, arg1, arg2, arg3, ...) arg3
#define _MIF_CH(e1, e2, ...) _MIF_AT(_V, ##__VA_ARGS__, e1, e2)
#define _MIF(p, e1, e2) _MIF_DE2(_MIF_CH, e1, e2, _MIF_DE(_MIF_CO, _I p))
#define mif(p, e1, e2) _MIF(p, e1, e2)

/* 
 * Enumeration Operator
 * To some degree, it can be implemented with _REC2
 * (with extended _DE to keep commas)
 * But an independent one is more useful
 * To generate more:
 * ("#define _REC1_%d(f, ...) _REC1_%d(f, ##__VA_ARGS__), f(%d, ##__VA_ARGS__)\n", i,i-1,i)
 */
#define _REC1_DE(f, ...) f(__VA_ARGS__)

#define _REC1_0(f, ...)
#define _REC1_1(f, ...) f(1, ##__VA_ARGS__)
#define _REC1_2(f, ...) _REC1_1(f, ##__VA_ARGS__), f(2, ##__VA_ARGS__)
#define _REC1_3(f, ...) _REC1_2(f, ##__VA_ARGS__), f(3, ##__VA_ARGS__)
#define _REC1_4(f, ...) _REC1_3(f, ##__VA_ARGS__), f(4, ##__VA_ARGS__)
#define _REC1_5(f, ...) _REC1_4(f, ##__VA_ARGS__), f(5, ##__VA_ARGS__)
#define _REC1_6(f, ...) _REC1_5(f, ##__VA_ARGS__), f(6, ##__VA_ARGS__)
#define _REC1_7(f, ...) _REC1_6(f, ##__VA_ARGS__), f(7, ##__VA_ARGS__)
#define _REC1_8(f, ...) _REC1_7(f, ##__VA_ARGS__), f(8, ##__VA_ARGS__)
#define _REC1_9(f, ...) _REC1_8(f, ##__VA_ARGS__), f(9, ##__VA_ARGS__)
#define _REC1_10(f, ...) _REC1_9(f, ##__VA_ARGS__), f(10, ##__VA_ARGS__)
#define _REC1_11(f, ...) _REC1_10(f, ##__VA_ARGS__), f(11, ##__VA_ARGS__)
#define _REC1_12(f, ...) _REC1_11(f, ##__VA_ARGS__), f(12, ##__VA_ARGS__)
#define _REC1_13(f, ...) _REC1_12(f, ##__VA_ARGS__), f(13, ##__VA_ARGS__)
#define _REC1_14(f, ...) _REC1_13(f, ##__VA_ARGS__), f(14, ##__VA_ARGS__)
#define _REC1_15(f, ...) _REC1_14(f, ##__VA_ARGS__), f(15, ##__VA_ARGS__)
#define _REC1_16(f, ...) _REC1_15(f, ##__VA_ARGS__), f(16, ##__VA_ARGS__)
#define _REC1_MAX 16
//...

// generate duplicates of f(i, ...), i = 1 ... n, seperated by comma
#define _REC1(n, f, ...) _REC1_DE(_REC1_##n, f ,##__VA_ARGS__)
// start from 0 rather than 1
#define _REC1Z(n, f, ...) f(0, ##__VA_ARGS__), _REC1(n, f, ## __VA_ARGS__)

// number enumeration(start from 0)
#define _NUZ(n) (_REC1Z(n, _I))
// number enumeration(start from 1)
#define _NU(n) (_REC1(n, _I))


/*
 * Generic Semi-Recursive Operator
 * This is not in LISP but fits C, behave as a deduction machine
 *
 * while _Q is expanding, _REC2_R* can not be expanded
 * because r is not defined before _Q is finished
 * 
 */ 
#define _REC2_CO(...) ,##__VA_ARGS__
#define _REC2_EC(a, ...) _V _REC2_CO(a)
#define _REC2_DE(f, ...) f(__VA_ARGS__)
#define _REC2_AT(arg0, arg1, arg2, arg3, ...) arg3
#define _REC2_Q(f, at, arg0, ...) _I(arg0)
#define __Q(r, ...) _REC2_AT(_V, ##__VA_ARGS__, r, _REC2_Q)
//_Q(r) expands _REC2_Q, _Q(r, a, ...) it expands to r
#define _Q(r, ...)  _REC2_DE(__Q, r, _REC2_EC(__VA_ARGS__))
/* here are 16 levels, you can generate more with format strings:
 * ( "#define _REC2_X%d(f, at, arg0, arg1, ...) _REC2_R%d(_REC2_X%d, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)\n", x, x+1, x+1 )
 * ( "#define _REC2_F%d(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)\n", x )
 * ( "#define _REC2_R%d(r, f, at, arg0, ...) _REC2_F%d(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)\n", x, x )
 */

//...
#define _REC2_MAX 15
#define _REC2_X15(f, at, arg0, arg1, ...) f(arg0, arg1) "Recursion Level Exceed!"
#define _REC2_F15(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R15(r, f, at, arg0, ...) _REC2_F15(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X14(f, at, arg0, arg1, ...) _REC2_R15(_REC2_X15, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F14(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R14(r, f, at, arg0, ...) _REC2_F14(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X13(f, at, arg0, arg1, ...) _REC2_R14(_REC2_X14, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F13(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R13(r, f, at, arg0, ...) _REC2_F13(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X12(f, at, arg0, arg1, ...) _REC2_R13(_REC2_X13, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F12(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R12(r, f, at, arg0, ...) _REC2_F12(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X11(f, at, arg0, arg1, ...) _REC2_R12(_REC2_X12, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F11(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R11(r, f, at, arg0, ...) _REC2_F11(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X10(f, at, arg0, arg1, ...) _REC2_R11(_REC2_X11, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F10(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R10(r, f, at, arg0, ...) _REC2_F10(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X9(f, at, arg0, arg1, ...) _REC2_R10(_REC2_X10, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F9(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R9(r, f, at, arg0, ...) _REC2_F9(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X8(f, at, arg0, arg1, ...) _REC2_R9(_REC2_X9, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F8(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R8(r, f, at, arg0, ...) _REC2_F8(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X7(f, at, arg0, arg1, ...) _REC2_R8(_REC2_X8, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F7(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R7(r, f, at, arg0, ...) _REC2_F7(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X6(f, at, arg0, arg1, ...) _REC2_R7(_REC2_X7, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F6(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R6(r, f, at, arg0, ...) _REC2_F6(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X5(f, at, arg0, arg1, ...) _REC2_R6(_REC2_X6, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F5(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R5(r, f, at, arg0, ...) _REC2_F5(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X4(f, at, arg0, arg1, ...) _REC2_R5(_REC2_X5, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F4(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R4(r, f, at, arg0, ...) _REC2_F4(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X3(f, at, arg0, arg1, ...) _REC2_R4(_REC2_X4, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F3(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R3(r, f, at, arg0, ...) _REC2_F3(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X2(f, at, arg0, arg1, ...) _REC2_R3(_REC2_X3, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F2(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R2(r, f, at, arg0, ...) _REC2_F2(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X1(f, at, arg0, arg1, ...) _REC2_R2(_REC2_X2, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F1(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R1(r, f, at, arg0, ...) _REC2_F1(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
#define _REC2_X0(f, at, arg0, arg1, ...) _REC2_R1(_REC2_X1, f, at, f(at, arg0, arg1, __VA_ARGS__), __VA_ARGS__)
#define _REC2_F0(f, at, arg0, r, ...) r(f, at, arg0, __VA_ARGS__)
#define _REC2_R0(r, f, at, arg0, ...) _REC2_F0(f, at, arg0,  _Q(r, __VA_ARGS__), __VA_ARGS__)
/*
 * f: a function receives at least 3 parameters, f(at, arg_prev, arg_next)
 * will be called recursively until there is no more than 2 arguments
 * the value of f(at, arg_prev, arg_next) will remain at where it was
 * at is static and can be used to pass an expression to be expanded
 */
#define _REC2(f, at, arg0, ...) _REC2_R0(_REC2_X0, f, at, arg0, ##__VA_ARGS__)

/*
 * last: get the last element of a list
 * if there is no enough elements, return nil
 */
#define _LAST_LR(f, p, n, ...) n
#define _LAST(arg0, ...) _REC2(_LAST_LR, _V, nil, arg0, ##__VA_ARGS__)
#define last(l) _LAST l

/*
 * cond: return the last element of the first expression
 * with its first element nonnil.
 * last is blocked until evaluation process ends.
 */
#define _COND_LR(f, p, n, ...) mif(car(p), p, n)
#define _COND_DE(f, ...) f(__VA_ARGS__)
#define cond(...) _COND_DE(last, _REC2(_COND_LR, nil, __VA_ARGS__))

/*
 * reverse:  reverse a list
 */
#define _REV_LR(f, p, n, ...) f(n, p)
#define _REV(...)  _REC2(_REV_LR, cons, nil, ##__VA_ARGS__)
#define reverse(l) _REV l

/*
 * append: append a list of lists
 */
#define _APPEND_LR(f, p, n, ...) f(p, n)
#define append(...) _REC2(_APPEND_LR, _APPEND1, nil, ##__VA_ARGS__)

/*
 * Infix expression generator
 * it is very intereting to see that
 * ifxgen(+, (a,b,c)) become expression ((a)+(b))+(c)
 */
#define _INFIX(op, x, y, ...) (x)op(y)
#define _INFIX_GEN_DE(f, ...) f(__VA_ARGS__)
#define _INFIX_GEN(op, arg0, ...) _REC2(_INFIX, op, arg0, ##__VA_ARGS__)
#define ifxgen(op, l) _INFIX_GEN_DE(_INFIX_GEN, op, _I l)

/*
 * Iterative Operator
 * It is very delicate that _REC1Z can behave as a generator
 * for _REC2 when parameters are not enough to expand _REC2_R*
 */
#define _IT_LR(f, i, ...) f(i)
#define _IT_AT(n, a) a
#define _ITER(n, f, i) _REC2(_IT_LR, f, i, _REC1(n, _IT_AT, t))
#define iter(n, f, i) _ITER(n, f, i)

/*
 * pick: pick n th element in the list
 * pick(0, l) always gets nil
 */
#define _PICK_DE(f, ...) f(__VA_ARGS__)
#define _PICK(n, l) _PICK_DE(car, _ITER(n, cdr, cons(nil, l)))
#define pick(n, l) _PICK(n, l)

/*
 * mapcar1: map a function to all the elements of a list
 * it is hard to implement mapcar without 2 _REC2
 * if you map f to nil, the output is still nil
 * if you want nil be a parameter of f, use a list of nil
 */
#define _MAP1_DE(f, ...) f(__VA_ARGS__)
#define _MAP1_CO(...) , ##__VA_ARGS__
#define _MAP1_LR(f, p, n, ...) _APPEND1(p, (f(n)))
#define _MAP1_F(f, ...) _REC2(_MAP1_LR, f, nil, ## __VA_ARGS__)
#define mapcar1(f, l) _MAP1_DE(_MAP1_F, f _MAP1_CO l)

/*
 * mapscan: for filter accumulation
 * only keep items that pass filter f
 */
#define _MAPSCAN_DE(f, ...) f(__VA_ARGS__)
#define _MAPSCAN_CO(...) ,##__VA_ARGS__
#define _MAPSCAN_LR(f, p, n, ...) mif(f(n), _APPEND1(p, (n)), p)
#define _MAPSCAN(f, ...) _REC2(_MAPSCAN_LR, f, nil, ##__VA_ARGS__)
#define mapscan(f, l) _MAPSCAN_DE(_MAPSCAN, f _MAPSCAN_CO l) 

/*
 * Incremental Operator
 * +1
 * ("#define _INC_%d %d", i, i+1)
 */
#define _INC_MAX 15
#define _INC_15 0
#define _INC_14 15
#define _INC_13 14
#define _INC_12 13
#define _INC_11 12
#define _INC_10 11
#define _INC_9 10
#define _INC_8 9
#define _INC_7 8
#define _INC_6 7
#define _INC_5 6
#define _INC_4 5
#define _INC_3 4
#define _INC_2 3
#define _INC_1 2
#define _INC_0 1
#define _INC(x) _INC_##x

/*
 * Decremental Operator
 * -1
 *  ("#define _DEC_%d %d", i, i-1)
 */
#define _DEC_MAX 15
#define _DEC_15 14
#define _DEC_14 13
#define _DEC_13 12
#define _DEC_12 11
#define _DEC_11 10
#define _DEC_10 9
#define _DEC_9 8
#define _DEC_8 7
#define _DEC_7 6
#define _DEC_6 5
#define _DEC_5 4
#define _DEC_4 3
#define _DEC_3 2
#define _DEC_2 1
#define _DEC_1 0
#define _DEC_0 _DEC_MAX
#define _DEC(x) _DEC_##x

/*
 * length: count the length of a list
 */
#define _LEN_LR(f, p, ...) f(p)
#define _LEN(...) _REC2(_LEN_LR, _INC, 0, ##__VA_ARGS__)
#define length(l) _LEN l

/* 
 * Macro Arithmetics
 * There must be x < _INC(or _DEC)_MAX, y < _REC1_MAX
 */
#define _MA_LR(f, p, ...) f(p)
#define _MA_ADD1(x, y) _REC2(_MA_LR, _INC, x, _REC1(y, _T))
#define add1(x, y) _MA_ADD1(x, y)

#define _MA_SUB1(x, y) _REC2(_MA_LR, _DEC, x, _REC1(y, _T))
#define sub1(x, y) _MA_SUB1(x, y)

#define _MATGEN_AT(x, ...) __VA_ARGS__
#define _MATGEN_DE(f, ...) f(__VA_ARGS__)
#define _MATGEN_AR(x, ...) _REC1(x, _MATGEN_AT, ##__VA_ARGS__)
#define _MATGEN(x, y) _MATGEN_DE(_MATGEN_AR, x, _REC1(y, _T))

#define _MA_MUL1(x, y) _REC2(_MA_LR, _INC, 0, _MATGEN(x, y))
#define mul1(x, y) _MA_MUL1(x, y)

/*
 * eq: test whether two integers are equal, if so return t, else return nil
 * _ZEROP tests if its parameter is equal to zero
 * it uses _MAC_SUB(x, y), so there must be: x < _DEC_MAX, y < _REC1_MAX
 */
#define _Z0 _V, nil
#define _ZP_DE(f, ...) f(__VA_ARGS__)
#define _ZP_AT(arg0, arg1, ...) arg1
#define _ZEROP(n) _ZP_DE(_ZP_AT, _Z##n, t)
#define _EQ_DE(f, ...) f(__VA_ARGS__)
#define _EQ(x, y) _EQ_DE(_ZEROP, _MA_SUB1(x, y))
#define eq(x, y) _EQ(x, y)

#endif
