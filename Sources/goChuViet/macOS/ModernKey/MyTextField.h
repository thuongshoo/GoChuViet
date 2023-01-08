//
//  MyTextField.h
//  OpenKey
//
//  Created by thuongshoo on 31 December 2022.
//  Copyright © 2022 thuongshoo. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@protocol MyTextFieldDelegate
@optional
-(void)onMyTextFieldKeyChange:(unsigned short)keyCode character:(unsigned short)character;
@end

@interface MyTextField : NSTextField<NSTextDelegate>
@property (weak, nonatomic) id<MyTextFieldDelegate> Parent;
@property unsigned short LastKeyCode;
@property unsigned short LastKeyChar;

-(void)setTextByChar:(unsigned short)chr;
@end
