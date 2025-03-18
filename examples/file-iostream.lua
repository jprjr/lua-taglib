local TagLib = require'TagLib'

-- our custom IOStream that uses
-- a Lua file. We just implement
-- the bare minimum needed to read
-- a file, and mark it as read-only.

local FileIOStream = {}
local FileIOStream_mt = {
  __index = FileIOStream
}

function FileIOStream:name()
  return self.name
end

function FileIOStream:readBlock(len)
  return self.file:read(len)
end

function FileIOStream:seek(offset, whence)
  if whence == 'Beginning' then
    whence = 'set'
  elseif whence == 'Current' then
    whence = 'cur'
  elseif whence == 'End' then
    whence = 'end'
  end
  self.file:seek(whence, offset)
end

function FileIOStream:tell()
  return self.file:seek()
end

function FileIOStream:length()
  local pos = self.file:seek()
  self.file:seek('end', 0)
  local len = self.file:seek()
  self.file:seek('set', pos)
  return len
end

function FileIOStream:isOpen()
  return true
end

function FileIOStream:readOnly()
  return true
end

-- create our backfile FileIOStream object
local f = setmetatable({ file = io.open(arg[1],'rb') }, FileIOStream_mt)

-- read an MP3 using our FileIOStream
local mp3 = TagLib.MPEG.File(TagLib.IOStream(f))

-- print a tag!
local tag = mp3:tag()
print('title',tag:title())
