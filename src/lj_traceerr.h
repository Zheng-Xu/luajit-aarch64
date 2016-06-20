/*
** Trace compiler error messages.
** Copyright (C) 2005-2016 Mike Pall. See Copyright Notice in luajit.h
*/

/* This file may be included multiple times with different TREDEF macros. */

#define FOR_ALL_TRACE_ERR(M) \
/* Recording. */ \
M(RECERR,	"error thrown or hook called during recording") \
M(TRACEUV,	"trace too short") \
M(TRACEOV,	"trace too long") \
M(STACKOV,	"trace too deep") \
M(SNAPOV,	"too many snapshots") \
M(BLACKL,	"blacklisted") \
M(RETRY,	"retry recording") \
M(NYIBC,	"NYI: bytecode %d") \
/* Recording loop ops. */ \
M(LLEAVE,	"leaving loop in root trace") \
M(LINNER,	"inner loop in root trace") \
M(LUNROLL,	"loop unroll limit reached") \
/* Recording calls/returns. */ \
M(BADTYPE,	"bad argument type") \
M(CJITOFF,	"JIT compilation disabled for function") \
M(CUNROLL,	"call unroll limit reached") \
M(DOWNREC,	"down-recursion, restarting") \
M(NYIFFU,	"NYI: unsupported variant of FastFunc %s") \
M(NYIRETL,	"NYI: return to lower frame") \
/* Recording indexed load/store. */ \
M(STORENN,	"store with nil or NaN key") \
M(NOMM,	"missing metamethod") \
M(IDXLOOP,	"looping index lookup") \
M(NYITMIX,	"NYI: mixed sparse/dense table") \
/* Recording C data operations. */ \
M(NOCACHE,	"symbol not in cache") \
M(NYICONV,	"NYI: unsupported C type conversion") \
M(NYICALL,	"NYI: unsupported C function type") \
/* Optimizations. */ \
M(GFAIL,	"guard would always fail") \
M(PHIOV,	"too many PHIs") \
M(TYPEINS,	"persistent type instability") \
/* Assembler. */ \
M(MCODEAL,	"failed to allocate mcode memory") \
M(MCODEOV,	"machine code too long") \
M(MCODELM,	"hit mcode limit (retrying)") \
M(SPILLOV,	"too many spill slots") \
M(BADRA,	"inconsistent register allocation") \
M(NYIIR,	"NYI: cannot assemble IR instruction %d") \
M(NYIPHI,	"NYI: PHI shuffling too complex") \
M(NYICOAL,	"NYI: register coalescing too complex") \

/* Detecting unused error messages:
   awk -F, '/^TREDEF/ { gsub(/TREDEF./, ""); printf "grep -q LJ_TRERR_%s *.[ch] || echo %s\n", $1, $1}' lj_traceerr.h | sh
*/
