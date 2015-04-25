 //
//  ChatViewController.swift
//  SwiftParseChat
//
//  Created by Jesse Hu on 2/23/15.
//  Copyright (c) 2015 Jesse Hu. All rights reserved.
//

import UIKit
import Foundation
import MediaPlayer
import MobileCoreServices
import AVFoundation
 
 enum MMVoiceTransactionState {
    case MMVoiceTransactionStateIdle
    case MMVoiceTransactionStateInitial
    case MMVoiceTransactionStateRecording
    case MMVoiceTransactionStateProcessing
 };
 
 class MMMicrophoneButton : UIButton {
    var volumeLevel: Float32 = 0.0
    var recording: Bool = false
 }
 
 protocol MMVoiceController {
    var voiceTransactionState: MMVoiceTransactionState {get}
    var listener: MMListener! {get}
    var speakButton: MMMicrophoneButton {get}
    var currentText: String {get}
    
    var mindMeldApp: MMApp {get}
 }
 
class ChatViewController: JSQMessagesViewController, UICollectionViewDataSource, UIActionSheetDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate, UIGestureRecognizerDelegate, MMVoiceController {
    
    var voiceTransactionState: MMVoiceTransactionState
    var listener: MMListener! = nil
    var speakButton: MMMicrophoneButton = MMMicrophoneButton()
    var mindMeldApp: MMApp = MMApp()
    var currentText: String
    
    var timer: NSTimer = NSTimer()
    var isLoading: Bool = false
    
    var groupId: String = ""
    
    var users = [PFUser]()
    var messages = [JSQMessage]()
    var avatars = Dictionary<String, JSQMessagesAvatarImage>()
    
    var bubbleFactory = JSQMessagesBubbleImageFactory()
    var outgoingBubbleImage: JSQMessagesBubbleImage!
    var incomingBubbleImage: JSQMessagesBubbleImage!
    
    var blankAvatarImage: JSQMessagesAvatarImage!
    
    var senderImageUrl: String!
    var batchMessages = true
    
    var chatReplies = [String]()
    var replyCount = 0
    
    required init(coder aDecoder: NSCoder) {
        self.voiceTransactionState = MMVoiceTransactionState.MMVoiceTransactionStateIdle
        self.currentText = ""
        super.init(coder: aDecoder)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        
        var user = PFUser.currentUser()
        self.senderId = user.objectId
        self.senderDisplayName = user[PF_USER_FULLNAME] as! String
        
        outgoingBubbleImage = bubbleFactory.outgoingMessagesBubbleImageWithColor(UIColor.jsq_messageBubbleBlueColor())
        incomingBubbleImage = bubbleFactory.incomingMessagesBubbleImageWithColor(UIColor.jsq_messageBubbleLightGrayColor())
        
        blankAvatarImage = JSQMessagesAvatarImageFactory.avatarImageWithImage(UIImage(named: "profile_blank"), diameter: 30)
        
        isLoading = false
        
        // init chatReplies
        chatReplies.append("We heard you say...")
        chatReplies.append("I stayed at Alila Ubud. I came with my wife. We had a great stay here.  The spa facilities are outstanding, my wife really enjoyed it.")
        chatReplies.append("Many people have spoken about pool in this hotel. How did you find it?")
        chatReplies.append("In food, did you try the local cuisine they serve?")
        chatReplies.append("Great! Seems you had a good stay. Feel free to review any other aspect.")
        
        self.loadMessages()
        Messages.clearMessageCounter(groupId);
        
        // code for speech to text.
//        [self createTextFieldInputAccessoryView];
//        [self startMindMeld];
//        [self createListener];
//        [self createActivityIndicator];
//        [self addObservers];
        
        self.createTextFieldInputAccessoryView()
        self.startMindMeld()
        self.createListener()
    }
    
    func startMindMeld() {
        self.mindMeldApp = MMApp(appID: "2614aa679fb0f791a0c64942bb7e2f43351ec8c6")
        self.mindMeldApp.delegate = self
        weak var weakSelf = self
    //    self.mindMeldApp.start(nil)
    //    onSuccess
//    [self.mindMeldApp start:nil
//    onSuccess:^(id ignored) {
//    /**
//    *  (2)
//    *  Now that the SDK has been initialized, we'll set the delegate and
//    *  subscribe to updates to the documents list.
//    */
//    weakSelf.mindMeldApp.delegate = weakSelf;
//    weakSelf.mindMeldApp.activeSession.documents.useBothPushAndPull = NO;
//    [weakSelf.mindMeldApp.activeSession.documents startUpdates];
//    }
//    onFailure:nil];
    }

    
    func createTextFieldInputAccessoryView() {}
    
    override func viewDidAppear(animated: Bool) {
        super.viewDidAppear(animated)
        self.collectionView.collectionViewLayout.springinessEnabled = true
        timer = NSTimer.scheduledTimerWithTimeInterval(5.0, target: self, selector: "loadMessages", userInfo: nil, repeats: true)
        
//        if UIImagePickerController.isSourceTypeAvailable(UIImagePickerControllerSourceType.Camera) {
//            
//            
//            println("captureVideoPressed and camera available.")
//            
//            var imagePicker = UIImagePickerController()
//            
//            imagePicker.delegate = self
//            imagePicker.sourceType = .Camera;
//            imagePicker.mediaTypes = [kUTTypeMovie!]
//            imagePicker.allowsEditing = false
//            
//            imagePicker.showsCameraControls = true
//            
//            
//            self.presentViewController(imagePicker, animated: true, completion: nil)
//            
//        }
    }
    
    func eventListener(){
        // do nothing.
    }
    
    func createListener(){
        self.listener = MMListener()
        self.listener.continuous = true; // continuous speech recognition
        self.listener.interimResults = true;
        self.listener.language = "en-US"
        var finalStringAttributes = [String: UIColor]()
        var interimStringAttributes = [String: UIColor]()
        
        weak var weakSelf = self
        self.listener.onBeganRecording = { (listener: MMListener!) in
            weakSelf?.setVoiceTransactionState(MMVoiceTransactionState.MMVoiceTransactionStateRecording)
        }
        self.listener.onFinishedRecording = { (listener: MMListener!) in
            weakSelf?.setVoiceTransactionState(MMVoiceTransactionState.MMVoiceTransactionStateProcessing)
        }
        self.listener.onFinished = { (listener: MMListener!) in
            weakSelf?.setVoiceTransactionState(MMVoiceTransactionState.MMVoiceTransactionStateIdle)
        }
        self.listener.onVolumeChanged = {(listener: MMListener!, avgVolumeLevel: Float32, peakVolumeLevel: Float32) in
            weakSelf?.speakButton.volumeLevel = avgVolumeLevel
        }
        
        self.listener!.onResult = {(listener: MMListener!, newResult: MMListenerResult!) in
            if (count(newResult.transcript) > 0) {
                // use different text colors to indicate interim and final results
                
                finalStringAttributes[NSForegroundColorAttributeName] = UIColor.blackColor()
                interimStringAttributes[NSForegroundColorAttributeName] = UIColor.darkGrayColor()
                var text = NSMutableAttributedString()
                for result in listener.results {
                    var textAttributes = (result.final != nil) ? finalStringAttributes : interimStringAttributes;
                    var textSegment = NSAttributedString.init(string: result.transcript)
                    text.appendAttributedString(textSegment)
                }
                
                weakSelf?.currentText = text.string;
                print(text.string)
                
//                if (newResult.final) {
//                    [weakSelf addMindMeldTextEntry:weakSelf.label.text];
//                }
            }
        }
    }
    
    func setVoiceTransactionState(voiceTransactionState : MMVoiceTransactionState){
    
        let _voiceTransactionState = voiceTransactionState;
    
        switch (voiceTransactionState) {
            case MMVoiceTransactionState.MMVoiceTransactionStateRecording:
                    self.speakButton.recording = true;
                    break;
            case MMVoiceTransactionState.MMVoiceTransactionStateIdle: self.speakButton.recording = false; break;
            case MMVoiceTransactionState.MMVoiceTransactionStateInitial: self.speakButton.recording = false; break;
            case MMVoiceTransactionState.MMVoiceTransactionStateProcessing: self.speakButton.recording = false; break;
            default:
                    self.speakButton.recording = false;
                    break;
        }
//    
//        if (voiceTransactionState <= MMVoiceTransactionState.MMVoiceTransactionStateInitial) {
//            self.speakButton.enabled = YES;
//        }
    }
    
    override func viewWillDisappear(animated: Bool) {
        super.viewWillDisappear(animated)
        timer.invalidate()
    }
    
    // Mark: - Backend methods
    
    func loadMessagesOld() {
        if self.isLoading == false {
            self.isLoading = true
            // XXX: Add messages to start with
            
            var lastMessage = messages.last
            
            var query = PFQuery(className: PF_CHAT_CLASS_NAME)
            query.whereKey(PF_CHAT_GROUPID, equalTo: groupId)
            if lastMessage != nil {
                query.whereKey(PF_CHAT_CREATEDAT, greaterThan: lastMessage?.date)
            }
            query.includeKey(PF_CHAT_USER)
            query.orderByDescending(PF_CHAT_CREATEDAT)
            query.limit = 1
            query.findObjectsInBackgroundWithBlock({ (objects: [AnyObject]!, error: NSError!) -> Void in
                if error == nil {
                    self.automaticallyScrollsToMostRecentMessage = false
<<<<<<< HEAD
                    
                    for object in (objects as! [PFObject]!).reverse() {
                        
                        self.addMessage(object, localUrl: nil)
=======
                    for object in (objects as! [PFObject]!).reverse() {
                        self.addMessage(object)
>>>>>>> origin/master
                    }
                    if objects.count > 0 {
                        self.finishReceivingMessage()
                        self.scrollToBottomAnimated(false)
                    }
                    self.automaticallyScrollsToMostRecentMessage = true
                } else {
                    ProgressHUD.showError("Network error")
                }
                self.isLoading = false;
            })
        }
    }

    func loadMessages(){
        // load the image and intro message.
        // 1. load image.
        if self.isLoading == false {
        var message: JSQMessage!
        var mediaItem = JSQPhotoMediaItem(image: UIImage(named: "Infinity-Pool.jpg"))
        
        mediaItem.appliesMediaViewMaskAsOutgoing = false
        message = JSQMessage(senderId: "sksYN48b56", senderDisplayName: "SUH", date: NSDate(), media: mediaItem)
        messages.append(message)
        //mediaItem.image = UIImage(contentsOfFile: "Infinity-Pool.jpg")
        
//        pictureFile!.getDataInBackgroundWithBlock({ (imageData: NSData!, error: NSError!) -> Void in
//            if error == nil {
//                mediaItem.image = UIImage(data: imageData)
//                self.collectionView.reloadData()
//            }
//        })
//        users.append(user)
        // 2. load the text
        message = JSQMessage(senderId: "sksYN48b56", senderDisplayName: "SUH", date: NSDate(), text: "So how was your experience at Alila?")
        messages.append(message)
            self.isLoading = true
        }
        
    }
    
    func sendBotMessage(var text2: String){
        var message = JSQMessage(senderId: "sksYN48b56", senderDisplayName: "SUH", date: NSDate(), text: text2)
        messages.append(message)
    }
    
    func addMessage(object: PFObject, localUrl: NSURL? ) {
        var message: JSQMessage!
        
        var user = object[PF_CHAT_USER] as! PFUser
        var name = user[PF_USER_FULLNAME] as! String
        
        var videoFile = object[PF_CHAT_VIDEO] as? PFFile
        var pictureFile = object[PF_CHAT_PICTURE] as? PFFile
        
        print("user id: " + user.objectId)
        
        if videoFile == nil && pictureFile == nil {
            message = JSQMessage(senderId: user.objectId, senderDisplayName: name, date: NSDate(), text: (object[PF_CHAT_TEXT] as? String))
        }
        
        // XXX:
        if videoFile != nil {
            print("video url: " + String(stringInterpolationSegment: localUrl))
            var mediaItem = JSQVideoMediaItem(fileURL: localUrl, isReadyToPlay: true)
            message = JSQMessage(senderId: user.objectId, senderDisplayName: name, date: NSDate(), media: mediaItem)
        }
        
        if pictureFile != nil {
            var mediaItem = JSQPhotoMediaItem(image: nil)
            mediaItem.appliesMediaViewMaskAsOutgoing = (user.objectId == self.senderId)
            message = JSQMessage(senderId: user.objectId, senderDisplayName: name, date: NSDate(), media: mediaItem)
            mediaItem.image = UIImage(contentsOfFile: "Infinity-Pool.jpg")
            
            pictureFile!.getDataInBackgroundWithBlock({ (imageData: NSData!, error: NSError!) -> Void in
                if error == nil {
                    mediaItem.image = UIImage(data: imageData)
                    self.collectionView.reloadData()
                }
            })
        }
        
        users.append(user)
        messages.append(message)
    }
    
    func sendMessage(var text: String, video: NSURL?, picture: UIImage?) {
        var videoFile: PFFile!
        var pictureFile: PFFile!
        
        if let video = video {
            text = "[Video message]"
            videoFile = PFFile(name: "video.mp4", data: NSFileManager.defaultManager().contentsAtPath(video.path!))
            
//            videoFile.saveInBackgroundWithBlock({ (succeeed: Bool, error: NSError!) -> Void in
//                if error != nil {
//                    ProgressHUD.showError("Network error")
//                }
//            })
        }
        
        if let picture = picture {
            text = "[Picture message]"
            pictureFile = PFFile(name: "picture.jpg", data: UIImageJPEGRepresentation(picture, 0.6))
            pictureFile.saveInBackgroundWithBlock({ (suceeded: Bool, error: NSError!) -> Void in
                if error != nil {
                    ProgressHUD.showError("Picture save error")
                }
            })
        }
        
        var object = PFObject(className: PF_CHAT_CLASS_NAME)
        object[PF_CHAT_USER] = PFUser.currentUser()
        object[PF_CHAT_GROUPID] = self.groupId
        object[PF_CHAT_TEXT] = text
        object[PF_CHAT_CREATEDAT] = NSDate()
        print ("Date: " + String(stringInterpolationSegment: object.createdAt))
        if let videoFile = videoFile {
      //      videoFile.url = video   // XXX: hack.
            object[PF_CHAT_VIDEO] = videoFile
        }
        if let pictureFile = pictureFile {
            object[PF_CHAT_PICTURE] = pictureFile
        }
        addMessage(object, localUrl: video)
//        object.saveInBackgroundWithBlock { (succeeded: Bool, error: NSError!) -> Void in
//            if error == nil {
//                JSQSystemSoundPlayer.jsq_playMessageSentSound()
//                self.loadMessages()
//            } else {
//                ProgressHUD.showError("Network error")
//            }
//        }
        
//        PushNotication.sendPushNotification(groupId, text: text)
//        Messages.updateMessageCounter(groupId, lastMessage: text)
        if (self.replyCount == 0){
            self.sendBotMessage(self.chatReplies[self.replyCount++])
            self.sendBotMessage(self.chatReplies[self.replyCount++])
            self.sendBotMessage(self.chatReplies[self.replyCount++])
        }
        else {
            self.sendBotMessage(self.chatReplies[self.replyCount])
        }
        self.finishSendingMessage()
    }
    
    // MARK: - JSQMessagesViewController method overrides
    
    override func didPressSendButton(button: UIButton!, withMessageText text: String!, senderId: String!, senderDisplayName: String!, date: NSDate!) {
        self.sendMessage(text, video: nil, picture: nil)
    }
    
    override func didPressAccessoryButton(sender: UIButton!) {
        var action = UIActionSheet(title: nil, delegate: self, cancelButtonTitle: "Cancel", destructiveButtonTitle: nil, otherButtonTitles: "Take photo", "Take video", "Choose existing photo", "Choose existing video")
        action.showInView(self.view)
    }
    
    // MARK: - JSQMessages CollectionView DataSource
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, messageDataForItemAtIndexPath indexPath: NSIndexPath!) -> JSQMessageData! {
        return self.messages[indexPath.item]
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, messageBubbleImageDataForItemAtIndexPath indexPath: NSIndexPath!) -> JSQMessageBubbleImageDataSource! {
        var message = self.messages[indexPath.item]
        if message.senderId == self.senderId {
            return outgoingBubbleImage
        }
        return incomingBubbleImage
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, avatarImageDataForItemAtIndexPath indexPath: NSIndexPath!) -> JSQMessageAvatarImageDataSource! {
        return blankAvatarImage
        //        print ("index path: " + String(indexPath.item))
//        var user = self.users[indexPath.item]
//        if self.avatars[user.objectId] == nil {
//            var thumbnailFile = user[PF_USER_THUMBNAIL] as? PFFile
//            thumbnailFile?.getDataInBackgroundWithBlock({ (imageData: NSData!, error: NSError!) -> Void in
//                if error == nil {
//                    self.avatars[user.objectId as String] = JSQMessagesAvatarImageFactory.avatarImageWithImage(UIImage(data: imageData), diameter: 30)
//                    self.collectionView.reloadData()
//                }
//            })
//            return blankAvatarImage
//        } else {
//            return self.avatars[user.objectId]
//        }
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, attributedTextForCellTopLabelAtIndexPath indexPath: NSIndexPath!) -> NSAttributedString! {
        if indexPath.item % 3 == 0 {
            var message = self.messages[indexPath.item]
            return JSQMessagesTimestampFormatter.sharedFormatter().attributedTimestampForDate(message.date)
        }
        return nil;
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, attributedTextForMessageBubbleTopLabelAtIndexPath indexPath: NSIndexPath!) -> NSAttributedString! {
        var message = self.messages[indexPath.item]
        if message.senderId == self.senderId {
            return nil
        }
        
        if indexPath.item - 1 > 0 {
            var previousMessage = self.messages[indexPath.item - 1]
            if previousMessage.senderId == message.senderId {
                return nil
            }
        }
        return NSAttributedString(string: message.senderDisplayName)
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, attributedTextForCellBottomLabelAtIndexPath indexPath: NSIndexPath!) -> NSAttributedString! {
        return nil
    }
    
    // MARK: - UICollectionView DataSource
    
    override func collectionView(collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return self.messages.count
    }
    
    override func collectionView(collectionView: UICollectionView, cellForItemAtIndexPath indexPath: NSIndexPath) -> UICollectionViewCell {
        var cell = super.collectionView(collectionView, cellForItemAtIndexPath: indexPath) as! JSQMessagesCollectionViewCell
        
        var message = self.messages[indexPath.item]
        if message.senderId == self.senderId {
            cell.textView?.textColor = UIColor.whiteColor()
        } else {
            cell.textView?.textColor = UIColor.blackColor()
        }
        return cell
    }
    
    // MARK: - UICollectionView flow layout
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, layout collectionViewLayout: JSQMessagesCollectionViewFlowLayout!, heightForCellTopLabelAtIndexPath indexPath: NSIndexPath!) -> CGFloat {
        if indexPath.item % 3 == 0 {
            return kJSQMessagesCollectionViewCellLabelHeightDefault
        }
        return 0
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, layout collectionViewLayout: JSQMessagesCollectionViewFlowLayout!, heightForMessageBubbleTopLabelAtIndexPath indexPath: NSIndexPath!) -> CGFloat {
        var message = self.messages[indexPath.item]
        if message.senderId == self.senderId {
            return 0
        }
        
        if indexPath.item - 1 > 0 {
            var previousMessage = self.messages[indexPath.item - 1]
            if previousMessage.senderId == message.senderId {
                return 0
            }
        }
        
        return kJSQMessagesCollectionViewCellLabelHeightDefault
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, layout collectionViewLayout: JSQMessagesCollectionViewFlowLayout!, heightForCellBottomLabelAtIndexPath indexPath: NSIndexPath!) -> CGFloat {
        return 0
    }
    
    // MARK: - Responding to CollectionView tap events
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, header headerView: JSQMessagesLoadEarlierHeaderView!, didTapLoadEarlierMessagesButton sender: UIButton!) {
        println("didTapLoadEarlierMessagesButton")
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, didTapAvatarImageView avatarImageView: UIImageView!, atIndexPath indexPath: NSIndexPath!) {
        println("didTapAvatarImageview")
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, didTapMessageBubbleAtIndexPath indexPath: NSIndexPath!) {
        var message = self.messages[indexPath.item]
        if message.isMediaMessage {
            if let mediaItem = message.media as? JSQVideoMediaItem {
                var moviePlayer = MPMoviePlayerViewController(contentURL: mediaItem.fileURL)
                self.presentMoviePlayerViewControllerAnimated(moviePlayer)
                moviePlayer.moviePlayer.play()
            }
        }
    }
    
    override func collectionView(collectionView: JSQMessagesCollectionView!, didTapCellAtIndexPath indexPath: NSIndexPath!, touchLocation: CGPoint) {
        println("didTapCellAtIndexPath")
    }
    
    // MARK: - UIActionSheetDelegate
    
    func actionSheet(actionSheet: UIActionSheet, clickedButtonAtIndex buttonIndex: Int) {
        if buttonIndex != actionSheet.cancelButtonIndex {
            if buttonIndex == 1 {
                Camera.shouldStartCamera(self, canEdit: true, frontFacing: false)
            } else if buttonIndex == 2 {
                // call the listener.start.
                self.voiceTransactionState = MMVoiceTransactionState.MMVoiceTransactionStateRecording;
                self.listener.startListening()
                print("started listener!")
                Camera.shouldStartVideoCamera(self, canEdit: true, frontFacing: false)
            } else if buttonIndex == 3 {
                Camera.shouldStartPhotoLibrary(self, canEdit: true)
            } else if buttonIndex == 4 {
                Camera.shouldStartVideoLibrary(self, canEdit: true)
            }
        }
    }
    
    // MARK: - UIImagePickerControllerDelegate
    
    func imagePickerController(picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [NSObject : AnyObject]) {
        var video = info[UIImagePickerControllerMediaURL] as? NSURL
        var picture = info[UIImagePickerControllerEditedImage] as? UIImage
        
        self.sendMessage("", video: video, picture: picture)
        // XXX: listener.stop
        self.listener.stopListening()
        print("stop listening!")
        picker.dismissViewControllerAnimated(true, completion: nil)
    }
}
