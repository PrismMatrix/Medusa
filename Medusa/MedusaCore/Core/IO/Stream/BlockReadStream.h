// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#pragma once
#include "Core/IO/Stream/IStream.h"
#include "Core/IO/Stream/MemoryStream.h"
#include "Core/Pattern/Share.h"

MEDUSA_BEGIN;

class BlockReadStream :public IStream
{
public:
	BlockReadStream(const Share<const IStream>& stream,uint32 blockSize);
	virtual ~BlockReadStream(void);
	
	BlockReadStream(const BlockReadStream&) = delete;
	BlockReadStream& operator=(const BlockReadStream&) = delete;
	BlockReadStream(BlockReadStream&& other);
	BlockReadStream& operator=(BlockReadStream&& other);
public:
public:
	virtual bool Flush()override;
	virtual bool Close()override;
	virtual bool IsOpen()const override{ return mSourceStream->IsOpen(); }
	virtual bool IsEnd()const override;

	virtual uintp Position()const override;

	virtual bool Seek(intp offset, SeekOrigin direction = SeekOrigin::Current)const override;

	virtual bool SetLength(uintp val)override;

	virtual size_t ReadDataTo(MemoryData& outData, DataReadingMode mode = DataReadingMode::AlwaysCopy)const override;
	virtual size_t WriteData(const MemoryData& data, DataReadingMode mode = DataReadingMode::AlwaysCopy)override;

	virtual int PeekChar()const override;
	virtual int PeekWChar()const override;
	virtual int ReadChar()const override;
	virtual int ReadWChar()const override;
	virtual bool WriteChar(char val)override;
	virtual bool WriteChar(wchar val)override;

	virtual size_t ReadStringTo(HeapString& outString)const override;
	virtual size_t ReadStringTo(WHeapString& outString)const override;
	virtual size_t ReadLineToString(HeapString& outString, bool includeNewLine = true)const override;
	virtual size_t ReadLineToString(WHeapString& outString, bool includeNewLine = true)const override;
	virtual size_t WriteString(const StringRef& str, bool withNullTermitated = true) override;
	virtual size_t WriteString(const WStringRef& str, bool withNullTermitated = true) override;

	virtual bool CanRead()const override;
	virtual bool CanWrite()const  override{ return false; }
	virtual bool CanSeek()const  override{ return true; }
	virtual StreamDataOperation Operations()const override { return StreamDataOperation::ReadSeek; }
protected:
	virtual size_t LoadCurrentBlock()const;
	virtual size_t LoadBlockTo(uint blockIndex, MemoryStream& output)const = 0;
protected:
	Share<const IStream> mSourceStream;

	mutable MemoryStream mBuffer;
	mutable uintp mBufferLength;
	mutable uint mBlockIndex;
};


MEDUSA_END;