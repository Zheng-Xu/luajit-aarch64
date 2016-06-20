/*
** VM error messages.
** Copyright (C) 2005-2016 Mike Pall. See Copyright Notice in luajit.h
*/

/* This file may be included multiple times with different ERRDEF macros. */

#if LJ_TARGET_WINDOWS
#define MAY_HAVE_ERR_BADFPU(M) M(BADFPU,  "bad FPU precision (use D3DCREATE_FPU_PRESERVE with DirectX)")
#endif
#ifndef MAY_HAVE_ERR_BADFPU
#define MAY_HAVE_ERR_BADFPU(M)
#endif

#if LJ_HASJIT
#define MAY_HAVE_ERR_JITPROT(M) M(JITPROT, "runtime code generation failed, restricted kernel?")
#if LJ_TARGET_X86ORX64
#define MAY_HAVE_ERR_NOJIT(M) M(NOJIT,   "JIT compiler disabled, CPU does not support SSE2")
#else
#define MAY_HAVE_ERR_NOJIT(M) M(NOJIT,   "JIT compiler disabled")
#endif
#elif defined(LJ_ARCH_NOJIT)
#define MAY_HAVE_ERR_NOJIT(M) M(NOJIT,   "no JIT compiler for this architecture (yet)")
#else
#define MAY_HAVE_ERR_NOJIT(M) M(NOJIT,   "JIT compiler permanently disabled by build option")
#endif
#ifndef MAY_HAVE_ERR_JITPROT
#define MAY_HAVE_ERR_JITPROT(M)
#endif
#ifndef MAY_HAVE_ERR_NOJIT
#define MAY_HAVE_ERR_NOJIT(M)
#endif

#if !LJ_52
#define MAY_HAVE_ERR_XAMBIG(M) M(XAMBIG,  "ambiguous syntax (function call x new statement)")
#endif
#ifndef MAY_HAVE_ERR_XAMBIG
#define MAY_HAVE_ERR_XAMBIG(M)
#endif

#if LJ_HASFFI
#define MAY_HAVE_ERR_FFI(M) \
/* FFI errors. */ \
M(FFI_INVTYPE, "invalid C type") \
M(FFI_INVSIZE, "size of C type is unknown or too large") \
M(FFI_BADSCL,  "bad storage class") \
M(FFI_DECLSPEC,    "declaration specifier expected") \
M(FFI_BADTAG,  "undeclared or implicit tag " LUA_QS) \
M(FFI_REDEF,   "attempt to redefine " LUA_QS) \
M(FFI_NUMPARAM,    "wrong number of type parameters") \
M(FFI_INITOV,  "too many initializers for " LUA_QS) \
M(FFI_BADCONV, "cannot convert " LUA_QS " to " LUA_QS) \
M(FFI_BADLEN,  "attempt to get length of " LUA_QS) \
M(FFI_BADCONCAT,   "attempt to concatenate " LUA_QS " and " LUA_QS) \
M(FFI_BADARITH,    "attempt to perform arithmetic on " LUA_QS " and " LUA_QS) \
M(FFI_BADCOMP, "attempt to compare " LUA_QS " with " LUA_QS) \
M(FFI_BADCALL, LUA_QS " is not callable") \
M(FFI_NUMARG,  "wrong number of arguments for function call") \
M(FFI_BADMEMBER,   LUA_QS " has no member named " LUA_QS) \
M(FFI_BADIDX,  LUA_QS " cannot be indexed") \
M(FFI_BADIDXW, LUA_QS " cannot be indexed with " LUA_QS) \
M(FFI_BADMM,   LUA_QS " has no " LUA_QS " metamethod") \
M(FFI_WRCONST, "attempt to write to constant location") \
M(FFI_NODECL,  "missing declaration for symbol " LUA_QS) \
M(FFI_BADCBACK,    "bad callback")
#if LJ_OS_NOJIT
#define MAY_HAVE_ERR_CBACKOV(M) M(FFI_CBACKOV, "no support for callbacks on this OS")
#else
#define MAY_HAVE_ERR_CBACKOV(M) M(FFI_CBACKOV, "too many callbacks")
#endif
#define MAY_HAVE_ERR_FFI_NYI(M) \
M(FFI_NYIPACKBIT,  "NYI: packed bit fields") \
M(FFI_NYICALL, "NYI: cannot call this C function (yet)")
#endif
#ifndef MAY_HAVE_ERR_FFI
#define MAY_HAVE_ERR_FFI(M)
#endif
#ifndef MAY_HAVE_ERR_CBACKOV
#define MAY_HAVE_ERR_CBACKOV(M)
#endif
#ifndef MAY_HAVE_ERR_FFI_NYI
#define MAY_HAVE_ERR_FFI_NYI(M)
#endif


#define FOR_ALL_ERR(M) \
/* Basic error handling. */ \
M(ERRMEM,	"not enough memory") \
M(ERRERR,	"error in error handling") \
M(ERRCPP,	"C++ exception") \
/* Allocations. */ \
M(STROV,	"string length overflow") \
M(UDATAOV,	"userdata length overflow") \
M(STKOV,	"stack overflow") \
M(STKOVM,	"stack overflow (%s)") \
M(TABOV,	"table overflow") \
/* Table indexing. */ \
M(NANIDX,	"table index is NaN") \
M(NILIDX,	"table index is nil") \
M(NEXTIDX,	"invalid key to " LUA_QL("next")) \
/* Metamethod resolving. */ \
M(BADCALL,	"attempt to call a %s value") \
M(BADOPRT,	"attempt to %s %s " LUA_QS " (a %s value)") \
M(BADOPRV,	"attempt to %s a %s value") \
M(BADCMPT,	"attempt to compare %s with %s") \
M(BADCMPV,	"attempt to compare two %s values") \
M(GETLOOP,	"loop in gettable") \
M(SETLOOP,	"loop in settable") \
M(OPCALL,	"call") \
M(OPINDEX,	"index") \
M(OPARITH,	"perform arithmetic on") \
M(OPCAT,	"concatenate") \
M(OPLEN,	"get length of") \
/* Type checks. */ \
M(BADSELF,	"calling " LUA_QS " on bad self (%s)") \
M(BADARG,	"bad argument #%d to " LUA_QS " (%s)") \
M(BADTYPE,	"%s expected, got %s") \
M(BADVAL,	"invalid value") \
M(NOVAL,	"value expected") \
M(NOCORO,	"coroutine expected") \
M(NOTABN,	"nil or table expected") \
M(NOLFUNC,	"Lua function expected") \
M(NOFUNCL,	"function or level expected") \
M(NOSFT,	"string/function/table expected") \
M(NOPROXY,	"boolean or proxy expected") \
M(FORINIT,	LUA_QL("for") " initial value must be a number") \
M(FORLIM,	LUA_QL("for") " limit must be a number") \
M(FORSTEP,	LUA_QL("for") " step must be a number") \
/* C API checks. */ \
M(NOENV,	"no calling environment") \
M(CYIELD,	"attempt to yield across C-call boundary") \
M(BADLU,	"bad light userdata pointer") \
M(NOGCMM,	"bad action while in __gc metamethod") \
MAY_HAVE_ERR_BADFPU(M) \
/* Standard library function errors. */ \
M(ASSERT,	"assertion failed!") \
M(PROTMT,	"cannot change a protected metatable") \
M(UNPACK,	"too many results to unpack") \
M(RDRSTR,	"reader function must return a string") \
M(PRTOSTR,	LUA_QL("tostring") " must return a string to " LUA_QL("print")) \
M(IDXRNG,	"index out of range") \
M(BASERNG,	"base out of range") \
M(LVLRNG,	"level out of range") \
M(INVLVL,	"invalid level") \
M(INVOPT,	"invalid option") \
M(INVOPTM,	"invalid option " LUA_QS) \
M(INVFMT,	"invalid format") \
M(SETFENV,	LUA_QL("setfenv") " cannot change environment of given object") \
M(CORUN,	"cannot resume running coroutine") \
M(CODEAD,	"cannot resume dead coroutine") \
M(COSUSP,	"cannot resume non-suspended coroutine") \
M(TABINS,	"wrong number of arguments to " LUA_QL("insert")) \
M(TABCAT,	"invalid value (%s) at index %d in table for " LUA_QL("concat")) \
M(TABSORT,	"invalid order function for sorting") \
M(IOCLFL,	"attempt to use a closed file") \
M(IOSTDCL,	"standard file is closed") \
M(OSUNIQF,	"unable to generate a unique filename") \
M(OSDATEF,	"field " LUA_QS " missing in date table") \
M(STRDUMP,	"unable to dump given function") \
M(STRSLC,	"string slice too long") \
M(STRPATB,	"missing " LUA_QL("[") " after " LUA_QL("%f") " in pattern") \
M(STRPATC,	"invalid pattern capture") \
M(STRPATE,	"malformed pattern (ends with " LUA_QL("%") ")") \
M(STRPATM,	"malformed pattern (missing " LUA_QL("]") ")") \
M(STRPATU,	"unbalanced pattern") \
M(STRPATX,	"pattern too complex") \
M(STRCAPI,	"invalid capture index") \
M(STRCAPN,	"too many captures") \
M(STRCAPU,	"unfinished capture") \
M(STRFMT,	"invalid option " LUA_QS " to " LUA_QL("format")) \
M(STRGSRV,	"invalid replacement value (a %s)") \
M(BADMODN,	"name conflict for module " LUA_QS) \
MAY_HAVE_ERR_JITPROT(M) \
MAY_HAVE_ERR_NOJIT(M) \
M(JITOPT,	"unknown or malformed optimization flag " LUA_QS) \
/* Lexer/parser errors. */ \
M(XMODE,	"attempt to load chunk with wrong mode") \
M(XNEAR,	"%s near " LUA_QS) \
M(XLINES,	"chunk has too many lines") \
M(XLEVELS,	"chunk has too many syntax levels") \
M(XNUMBER,	"malformed number") \
M(XLSTR,	"unfinished long string") \
M(XLCOM,	"unfinished long comment") \
M(XSTR,	"unfinished string") \
M(XESC,	"invalid escape sequence") \
M(XLDELIM,	"invalid long string delimiter") \
M(XTOKEN,	LUA_QS " expected") \
M(XJUMP,	"control structure too long") \
M(XSLOTS,	"function or expression too complex") \
M(XLIMC,	"chunk has more than %d local variables") \
M(XLIMM,	"main function has more than %d %s") \
M(XLIMF,	"function at line %d has more than %d %s") \
M(XMATCH,	LUA_QS " expected (to close " LUA_QS " at line %d)") \
M(XFIXUP,	"function too long for return fixup") \
M(XPARAM,	"<name> or " LUA_QL("...") " expected") \
MAY_HAVE_ERR_XAMBIG(M) \
M(XFUNARG,	"function arguments expected") \
M(XSYMBOL,	"unexpected symbol") \
M(XDOTS,	"cannot use " LUA_QL("...") " outside a vararg function") \
M(XSYNTAX,	"syntax error") \
M(XFOR,	LUA_QL("=") " or " LUA_QL("in") " expected") \
M(XBREAK,	"no loop to break") \
M(XLUNDEF,	"undefined label " LUA_QS) \
M(XLDUP,	"duplicate label " LUA_QS) \
M(XGSCOPE,	"<goto %s> jumps into the scope of local " LUA_QS) \
/* Bytecode reader errors. */ \
M(BCFMT,	"cannot load incompatible bytecode") \
M(BCBAD,	"cannot load malformed bytecode") \
MAY_HAVE_ERR_FFI(M) \
MAY_HAVE_ERR_CBACKOV(M) \
MAY_HAVE_ERR_FFI_NYI(M)

/* Detecting unused error messages:
   awk -F, '/^ERRDEF/ { gsub(/ERRDEF./, ""); printf "grep -q LJ_ERR_%s *.[ch] || echo %s\n", $1, $1}' lj_errmsg.h | sh
*/
