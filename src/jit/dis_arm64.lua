----------------------------------------------------------------------------
-- LuaJIT ARM64 disassembler module.
--
-- Copyright (C) 2005-2016 Mike Pall. All rights reserved.
-- Released under the MIT license. See Copyright Notice in luajit.h
----------------------------------------------------------------------------
-- This is a helper module used by the LuaJIT machine code dumper module.
--
-- It disassembles most user-mode AArch64 instructions
-- NYI: Advanced SIMD and VFP instructions.
------------------------------------------------------------------------------

local type = type
local sub, byte, format = string.sub, string.byte, string.format
local match, gmatch, gsub = string.match, string.gmatch, string.gsub
local concat = table.concat
local bit = require("bit")
local band, bor, ror, tohex = bit.band, bit.bor, bit.ror, bit.tohex
local lshift, rshift, arshift = bit.lshift, bit.rshift, bit.arshift
local bxor = bit.bxor

local function write_word(f,x)
  local b1 = string.char(x%256) x = (x-x%256)/256
  local b2 = string.char(x%256) x = (x-x%256)/256
  local b3 = string.char(x%256) x = (x-x%256)/256
  local b4 = string.char(x%256) x = (x-x%256)/256
  f:write(b1,b2,b3,b4)
end

------------------------------------------------------------------------------

local map_regs = {}

map_regs.x = {[31] = "sp"}
for i=0,30 do map_regs.x[i] = "x"..i; end

map_regs.w = {[31] = "wsp"}
for i=0,30 do map_regs.w[i] = "w"..i; end

map_regs.d = {}
for i=0,31 do map_regs.d[i] = "d"..i; end

map_regs.s = {}
for i=0,31 do map_regs.s[i] = "s"..i; end

------------------------------------------------------------------------------

-- Output a nicely formatted line with an opcode and operands.
local function putop(ctx, text, operands)
  local pos = ctx.pos
  local extra = ""
  if ctx.rel then
    local sym = ctx.symtab[ctx.rel]
    if sym then
      extra = "\t->"..sym
    elseif band(ctx.op, 0x0e000000) ~= 0x0a000000 then  --TODO: check
      extra = "\t; 0x"..tohex(ctx.rel)
    end
  end
  if ctx.hexdump > 0 then
    ctx.out(format("%08x:  %s  %-5s %s%s\n",
      ctx.addr+pos, tohex(ctx.op), text, concat(operands, ", "), extra))
  else
    ctx.out(format("%08x:  %-5s %s%s\n",
      ctx.addr+pos, text, concat(operands, ", "), extra))
  end
  ctx.pos = pos + 4
end

local function objdump(ctx)
  local out = io.open(".tmp.o", "wb")
  write_word(out, ctx.op)
  local addr = tohex(ctx.addr+ctx.pos):gsub("^0*(.-)", "%1")
  out:close()
  local cmd = "objdump -D -bbinary -maarch64 --adjust-vma ".." 0x"
              ..addr.." ".." .tmp.o | grep '"..addr..":'"
  local handle = io.popen(cmd)
  local result = handle:read("*a")
  result = result:gsub("^%s*[0-9a-zA-Z]*:%s*(.-)%s*$", "%1")
  handle:close()
  return putop(ctx, result, {""})
end

local function match_reg(p, pat, regnum)
  return map_regs[match(pat, p.."%w-([xwds])")][regnum]
end

-- Disassemble a single instruction.
local function disass_ins(ctx)
  local pos = ctx.pos
  local b0, b1, b2, b3 = byte(ctx.code, pos+1, pos+4)
  local op = bor(lshift(b3, 24), lshift(b2, 16), lshift(b1, 8), b0) -- order depends on endian
  ctx.op = op
  ctx.rel = nil
  return objdump(ctx)
end

------------------------------------------------------------------------------

-- Disassemble a block of code.
local function disass_block(ctx, ofs, len)
  if not ofs then ofs = 0 end
  local stop = len and ofs+len or #ctx.code
  ctx.pos = ofs
  ctx.rel = nil
  while ctx.pos < stop do disass_ins(ctx) end
end

-- Extended API: create a disassembler context. Then call ctx:disass(ofs, len).
local function create(code, addr, out)
  local ctx = {}
  ctx.code = code
  ctx.addr = addr or 0
  ctx.out = out or io.write
  ctx.symtab = {}
  ctx.disass = disass_block
  ctx.hexdump = 8
  return ctx
end

-- Simple API: disassemble code (a string) at address and output via out.
local function disass(code, addr, out)
  create(code, addr, out):disass()
end

-- Return register name for RID.
local function regname(r)
  if r < 32 then return map_regs.x[r] end
  return map_regs.d[r-32]
end

-- Public module functions.
return {
  create = create,
  disass = disass,
  regname = regname
}
