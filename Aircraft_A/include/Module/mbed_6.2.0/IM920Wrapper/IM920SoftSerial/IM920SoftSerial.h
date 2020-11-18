
#include "BufferedSoftSerial.h"
#include "XString.h"


class IM920SoftSerial{

    //received format
    //xx,yyyy,zz: message...
    //xx: Node number
    //yyyy: ID number
    //zz: RSSI value
    enum class MessageType{
        Node,
        ID,
        RSSI,
        Message
    };

    BufferedSoftSerial ss_;

    MessageType type_ = MessageType::Node;

    char c = '\0';
    xString received_ = "";

    bool reading_ = false;
    bool readingMessage_ = false;

public:

    IM920SoftSerial(PinName tx, PinName rx)
    :ss_(tx, rx)
    { 
        ss_.baud(19200);
    }

    void update(){
        if(!ss_.readable()){
            return;
        }
        
        c = static_cast<char>(ss_.getc());

        switch (type_) {
        case MessageType::Node:
        receiveNode();
        break;

        case MessageType::ID:
        receiveID();
        break;

        case MessageType::RSSI:
        receiveRSSI();
        break;

        case MessageType::Message:
        receiveMessage();
        break;

        }
        if(ss_.readable()){
            const char c = static_cast<char>(ss_.getc());


            if(c == '\n'){
                reading_ = false;
            }

            if(readingMessage_){
                received_ += static_cast<char>(ss_.getc());
            }
        }
    }

    xString received()const{
        return received_;
    }

    bool readable(){
        return ss_.readable();
    }

private:

    void receiveNode(){
        if(c == ':'){
            printf("node end \r\n");
            type_ = MessageType::ID;
        }
    }

    void receiveID(){
        if(c == ':'){
            printf("id end \r\n");
            type_ = MessageType::RSSI;
        }
    }

    void receiveRSSI(){
        if(c == ' '){
            printf("rssi end \r\n");
            received_ = "";
            type_ = MessageType::Message;
        }
    }

    void receiveMessage(){
        if(c == '\n'){
            type_ = MessageType::Node;
            printf("kaigyo \r\n");
        }else{
            printf("msg \r\n");
            received_ += c;
        }
    }
};