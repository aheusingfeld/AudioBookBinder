//
//  AudioFile.h
//  AudioBookBinder
//
//  Created by Oleksandr Tymoshenko on 10-02-06.
//  Copyright 2010 Bluezbox Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface AudioFile : NSObject {
    NSString *filePath;
    NSString *file;
    NSNumber *duration;
    NSString *artist, *name, *album, *albumArtist, *genre, *composer;
    BOOL valid;
}

@property(readwrite, copy) NSString *filePath;
@property(readwrite, copy) NSString *file;
@property(readwrite, copy) NSNumber *duration;
@property(readwrite, assign) BOOL valid;
@property(readwrite, copy) NSString *artist;
@property(readwrite, copy) NSString *name;
@property(readwrite, copy) NSString *album;
@property(readwrite, copy) NSString *year;
@property(readwrite, copy) NSString *genre;
@property(readwrite, copy) NSString *composer;



- (id) initWithPath:(NSString*)path;
- (void) dealloc;

// private function
NSString* getPropertyFromAudioFile(NSString *propName, NSDictionary *properties);
- (void) updateInfo;
@end
