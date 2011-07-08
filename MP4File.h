//
//  Copyright (c) 2009, Oleksandr Tymoshenko <gonzo@bluezbox.com>
//  All rights reserved.
// 
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//  1. Redistributions of source code must retain the above copyright
//     notice unmodified, this list of conditions, and the following
//     disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
// 
//  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  SUCH DAMAGE.
//

#import <Cocoa/Cocoa.h>

@class MP4Atom;

@interface MP4File : NSObject {
    NSFileHandle *_fh;
    NSString *artist;
    NSString *title;
    NSString *album;
    NSString *genre;
    NSString *composer;
    NSString *year;
    NSString *comment;
    NSString *coverFile;
    unsigned short track, tracksTotal;
    BOOL gaplessPlay;
}

@property (readwrite, copy) NSString *artist;
@property (readwrite, copy) NSString *album;
@property (readwrite, copy) NSString *title;
@property (readwrite, copy) NSString *genre;
@property (readwrite, copy) NSString *composer;
@property (readwrite, copy) NSString *comment;
@property (readwrite, copy) NSString *year;
@property (readwrite, copy) NSString *coverFile;
@property (readwrite, assign) unsigned short track, tracksTotal;
@property (readwrite, assign) BOOL gaplessPlay;

-(void) dealloc;
-(id) initWithFileName: (NSString*)fileName;
-(id) findAtom: (NSString*)atomName;
-(NSData*) encodeMetaDataAtom: (NSString*)name value:(NSData*)value type:(UInt32)type;
-(BOOL) updateFile;
-(NSData*) encodeHDLRAtom;
-(void) reserveSpace:(UInt64)size at:(UInt64)offset;
-(void) fixSTCOAtomBy:(UInt64)shift;
-(void) fixupAtom: (MP4Atom*)atom;

@end
