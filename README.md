# lua-taglib

Lua bindings to [TagLib](https://taglib.org/).

Compatible with TagLib 1.0 through 2.0.2.

Only requires C++ 98 to compile for TagLib 1.0 through 1.13,
C++11 for TagLib 2.0 (note: TagLib itself may require a newer
version of C++ compared to this binding).

## Installation

### Building with cmake

If you have Lua and TagLib, cmake should find everything
you need.

You can specify a particular Lua version by setting
`LUA_VERSION`. Alternatively, you can specify the
directory for Lua headers by setting `LUA_INCLUDE_DIR`.
If you do this - then on Windows systems you'll
also need to set `LUA_LIBRARY`.

Similarly you can specify the include/library folders for TagLib
by setting `TAGLIB_INCLUDE_DIR` and `TAGLIB_LIBRARY`.

If you're linking against a static version of TagLib, you
probably need to link against zlib - you can define
`TAGLIB_USE_ZLIB`, it will try to find and link with
zlib. And like with Lua and TagLib - you can define
`ZLIB_INCLUDE_DIR` and `ZLIB_LIBRARY` to specify where to
find Zlib headers and the library.

For example, if you have a static build of TagLib at
`/opt/taglib-static` you could probably build with:

```
cmake -B build -DTAGLIB_INCLUDE_DIR=/opt/taglib-static/include/taglib -DTAGLIB_LIBRARY=/opt/taglib-static/lib/libtag.a -DTAGLIB_USE_ZLIB=ON
make -C build
```

### With LuaRocks

This module is available as a LuaRock. Building the rock requires
cmake, and it accepts the `TAGLIB_INCLUDE_DIR`, `TAGLIB_LIBRARY`,
`TAGLIB_USE_ZLIB`, `ZLIB_INCLUDE_DIR`, and `ZLIB_LIBRARY` arguments that cmake uses.

For example - if you want to install with LuaRocks and have a static
build of TagLib at `/opt/taglib-static`:

```
luarocks install TagLib TAGLIB_INCLUDE_DIR=/opt/taglib-static/include/taglib TAGLIB_LIBRARY=/opt/taglib-static/lib/libtag.a TAGLIB_USE_ZLIB=ON
```

## Usage

I tried to mimic using TagLib in C++ - so namespaces and classes are
generally represented as modules. You can `require` individual
namespaces and modules, or you can just require the main `TagLib`
module and access everything from there.

For example, in TagLib with C++, if you wanted to open
a FileRef and get the title tag, you could do something like:

```c++
TagLib::FileRef f = TagLib::FileRef("/path/to/file.mp3");
TagLib::String artist = f.tag()->artist();
```

In Lua, this would be:

```lua
local TagLib = require'TagLib'
local f = TagLib.FileRef('/path/to/file.mp3')
local artist = f:tag():artist()
-- artist is a UTF-8 encoded Lua string
```

or:

```lua
local FileRef = require'TagLib.FileRef'
local f = FileRef('/path/to/file.mp3')
local artist = f:tag():artist()
-- artist is a UTF-8 encoded Lua string
```

Most objects are represented as Lua userdata, with
metatables set to access C++ methods.

You can manually cast objects into different types,
every class has a `cast` function you can use for this.
If the casting fails because you're trying to make an
impossible cast (like a `TagLib::File` into a `TagLib::Tag`) - that
will throw a Lua error since that's a programming
error. If the cast fails for some other reason, it will
return `nil`.

Example, if you want to do things with an ID3v2 AttachedPicture Frame:

```lua
local TagLib = require'TagLib'
local mp3 = TagLib.MPEG.File('/path/to/mp3')
local frames = mp3:frameList('APIC')
local pictureFrame = TagLib.ID3v2.AttachedPictureFrame.cast(frames[1])
local pictureType = pictureFrame:type()
```

Objects will hold a reference to their "parent" object to prevent
early garbage-collection. Meaning it's safe to do things like:

```lua

local TagLib = require'TagLib'

local function getPictures(path)
  local mp3 = TagLib.MPEG.File(path)
  local pictureFrames = {}
  for i,f in ipairs(mp3:ID3v2Tag():frameList('APIC')) do
    pictureFrames[i] = TagLib.ID3v2.AttachedPictureFrame.cast(f)
  end
  return pictureFrames
end

local pictures = getPictures('/path/to/mp3')

-- variables declared in getPictures are now out-of-scope but
-- won't be garbage-collected until after the "pictures" variable
-- is garbage-collected.

```


### Deviations from TagLib

This library tries to follow TagLib pretty closely so you can follow along
with the TagLib docs but there's a few special cases to be aware of:

#### `TagLib::String`

[`TagLib::String`](https://taglib.org/api/classTagLib_1_1String.html) objects are always
converted to UTF-8, and then returned to Lua as a Lua string.

Similarly - any Lua string passed is assumed to be UTF-8,and will
be converted to a `TagLib::String`.

If you have a string in some other encoding - you'll need to convert it to
UTF-8 before calling any TagLib method that accepts a string.

#### `TagLib::ByteVector`

[`TagLib::ByteVector`](https://taglib.org/api/classTagLib_1_1ByteVector.html) objects
are converted to a Lua string (as-is, no encoding conversions).

And similarly - any Lua string can be used as a `TagLib::ByteVector`.

If there is a function that can accept either a `TagLib::String` or a `TagLib::ByteVector`,
`TagLib::String` wins.

You can explicitly convert a Lua string into a `TagLib::ByteVector`, should you need to:

```lua
local TagLib = require'TagLib'
local bv = TagLib.ByteVector('Some String')
```

There's only two places I know of where you distinguish between `TagLib::String` and `TagLib::ByteVector`:

* Creating a `TagLib::ASF::Attribute`
* Creating a `TagLib::MP4::Item`

#### Lists and Maps

TagLib lists and maps can be represented as Lua tables, or as userdata.

For functions that just return a list or map, like any function that
returns a `TagLib::StringList` or `TagLib::PropertyMap` - those will
be returned as regular Lua tables. Lists will have integer keys
and can be iterated with `ipairs`, maps will have string keys.

For functions that return a list or map *reference*, like
`TagLib::ID3v2::frameListMap` - that will be a userdata, with
appropriate metamethods to iterate and access the table (`__index`,
`__pairs`,`__len` (for lists), `__ipairs` (for lists)).

The reasoning behind this is, the reference can be updated
(you could add a new `TagLib::ID3v2::Frame` to a tag, for example),
so using the userdata allows us to hold on to the reference
and always have the latest values.

One thing to note is anytime you access one of these map/list
references, you're creating a new userdata object. So if you were
to do something like:

```
local title1 = frameListMap['TIT2']
local title2 = frameListMap['TIT2']
```

Then `title1` and `title2` will be two different objects.

If you're using Lua 5.1 or LuaJIT - these don't honor the `__pairs`
and `__ipairs` metamethods. I have compatible `pairs` and `ipairs`
functions you can use:

```lua
local pairs = require'TagLib.pairs'
local ipairs = require'TagLib.ipairs'
```

You could remove `local` if you want to override the global `pairs`/`ipairs` but,
I wouldn't really recommend that.

It's safe to use these compatibility functions on Lua 5.2+ - they'll
just return the default `pairs` and `ipairs`.

It's also pretty easy to make your own 5.2-compatible functions
in Lua. I think in theory that can have better performance in LuaJIT
but it's probably negligible, since you'll be hitting the C API pretty
often anyway.

```lua

local raw_pairs = pairs
local pairs = function(t)
  local metatable = debug.getmetatable(t)
  if metatable and metatable.__pairs then
    return metatable.__pairs(t)
  end
  return raw_pairs(t)
end
```

#### Setter functions

Various setter functions (that return `void` in C++) will instead return the
userdata. This allows you to chain calls, like:

```lua
local mp3 = TagLib.MPEG.File('/path/to/mp3')
mp3:tag():setTitle('Some Title'):setArtist('SomeArtist')
mp3:save()
```

You could do some pretty complex things like, if you wanted to
create a list of ID3v2 chapter frames and a table of contents frame:

```lua
local mp3 = TagLib.MPEG.File('/path/to/mp3')
local tag = mp3:ID3v2Tag()

for _,frame in ipairs({
  TagLib.ID3v2.ChapterFrame(
    'chap01',
    0, 1000,
    0xffffffff, 0xffffffff,
    {
      TagLib.ID3v2.TextIdentificationFrame('TIT2',TagLib.String.Type.UTF8):setText('Chapter 1')
    }
  ),
  TagLib.ID3v2.ChapterFrame(
    'chap01',
    2000, 3000,
    0xffffffff, 0xffffffff,
    {
      TagLib.ID3v2.TextIdentificationFrame('TIT2',TagLib.String.Type.UTF8):setText('Chapter 2')
    }
  ),
  TagLib.ID3v2.TableOfContentsFrame(
    'toc',
    { 'chap01', 'chap02' }
  )
  }) do
  tag:addFrame(frame)
end
mp3:save()
```

#### FLAC::File and MPEG::File with IOStream

In TagLib editions prior to 2.0, the order of parameters to create FLAC::File
or MPEG::File object with an IOStream is different. This library only presents
the 2.0+ ordering.

## Limitations/gotchas

### Likely not compatible with Lua Lanes

The library currently relies on using `LUA_REGISTRYINDEX` to store metatables,
I believe this may limit the usefulness of the library with Lua Lanes and
other multithreaded solutions. I may consider changing this, but it would
be a lot of effort.

#### Custom IO with coroutines probably won't work

It's possible to create Lua-backed IOStream objects and load files, but
if you're looking to integrate this into say, OpenResty or cqueues (or
anything else that uses coroutines to have non-blocking I/O) - that
likely won't work.

I'm unsure how to tackle this - newer versions of
Lua do have a mechanism for creating continuation functions, but
at the point that I'm using `lua_call` to call Lua functions in
an IOStream object - I'm pretty deep in the call stack. Said
call stack is lost when a Lua coroutine yields, because
`lua_callk` doesn't return when `coroutine.yield` is called.

I'm not sure if this will ever be supported.


## License

MIT. See file `LICENSE`.

