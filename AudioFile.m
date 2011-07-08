//
//  AudioFile.m
//  AudioBookBinder
//
//  Created by Oleksandr Tymoshenko on 10-02-06.
//  Copyright 2010 Bluezbox Software. All rights reserved.
//

#import <AudioToolbox/AudioToolbox.h>

#import "AudioFile.h"

@implementation AudioFile

- (id) initWithPath:(NSString*)path
{
    if ((self = [super init]))
    {
        self.filePath = [path stringByExpandingTildeInPath];
        self.file = [filePath lastPathComponent];
        self.duration = [[NSNumber alloc] initWithInt:-1];
        self.valid = NO;
        self.name = @"";
        [self updateInfo];
    }
    return self;
}

- (void) dealloc
{
    self.filePath = nil;
    self.file = nil;
    self.name = nil;
	[properties release];
    [super dealloc];
}

@synthesize filePath, file, duration, valid, name, properties;

/**
 * Tries to read the specified property from the internal list of properties read from the file.
 * IMPORTANT: "updateInfo" method must have finished before this can be called!!
 *
 * @return value of the property as UTF8-String
 * @see - (NSString*) getPropertyFromAudioFile:(NSString *)propName:(NSDictionary *)props
 */
- (NSString*) getPropertyFromAudioFile: (NSString *)propName
{
	return [self getPropertyFromAudioFile:propName:properties];
}

/**
 * Tries to read the specified property as UTF8-String from the specified NSDictionary.
 * IMPORTANT: "updateInfo" method must have finished before this can be called!!
 */
- (NSString*) getPropertyFromAudioFile:(NSString *)propName:(NSDictionary *)props
{
	id obj = [props objectForKey:propName];
	
	if (obj != nil)
	{
		return [NSString stringWithUTF8String:[obj UTF8String]];
	}
	return @"";
}

- (void) updateInfo
{
    // NSString *extension = [[self.filePath pathExtension] lowercaseString];
    OSStatus status;
    AudioFileID audioFile;
    CFURLRef url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                                                 (CFStringRef)self.filePath,
                                                 kCFURLPOSIXPathStyle, FALSE);
    if (AudioFileOpenURL(url, 0x01, 0, &audioFile) == noErr) {        
        UInt32 len = sizeof(NSTimeInterval);
        NSTimeInterval dur;
        if (AudioFileGetProperty(audioFile, kAudioFilePropertyEstimatedDuration, &len, &dur) == noErr) 
            self.duration = [[NSNumber alloc] initWithInt:(dur*1000)];

        UInt32 writable = 0, size;
        status = AudioFileGetPropertyInfo(audioFile, 
            kAudioFilePropertyInfoDictionary, &size, &writable);

        if ( status == noErr ) {
            CFDictionaryRef info = NULL;
            status = AudioFileGetProperty(audioFile, 
                kAudioFilePropertyInfoDictionary, &size, &info);
            if ( status == noErr ) {
				
				// uncomment this to see the list of property keys in your console
				// NSLog(@"%@", (NSDictionary*) info);
				
				NSMutableDictionary *aProps = [[NSMutableDictionary alloc] init];
				[ aProps addEntriesFromDictionary: (NSDictionary*) info ];                
				self.properties = aProps;
				[aProps release];
                
				self.name = [self getPropertyFromAudioFile:@"title": (NSDictionary*) info];
			}
        }
        self.valid = YES;
        AudioFileClose(audioFile);
    }

    CFRelease(url);
}

@end
