//UDS Protocol manipulation by using c++ 

#include <iostream>
#include <string>
using namespace std;
class UDS_Protcole{
protected:
 
 unsigned int  frame_UDS[4];
 unsigned int  SID_chek[10]={0x10,0x11,0x27,0x28,0x83,0x85,0x86,0x87,0x62,0x3E};
 unsigned int  SBF_chek_10[11]={0x01,0x02,0x03,0x04,0x05,0x3F,0x40,0x5F,60,0x7E,0x7F};
 unsigned int  SBF_chek_11[28]={0x00,0x01,0x02,0x03};
public:
void diagnostic_request(){
 cout<<"enter your Requset_frame"<<endl;
for (int i=0;i<4;i++){
    cin>>hex>>frame_UDS[i];
}
}
void Display_diagnostic_frame(){
 cout<<"your frame [SID+SBF+DATA]"<<endl;
 cout<<hex<<frame_UDS[0];
 cout <<" ";
 cout<<hex<<frame_UDS[1]<<" ";;
 cout<<hex<<frame_UDS[2]<<" "<<frame_UDS[3];
 cout <<endl;

}
void diqgnostic_response (){
int c1=0, c2=0,NRC,n1=1,n2=2,n3;
    for (int i =0;i<11;i++){
        if(i<10 && frame_UDS[0]==SID_chek[i]){
          //"SID_chek_1"; 
          c1=1;
          n1=0;
        }

             
        if(i<11 && frame_UDS[1]==SBF_chek_10[i]){
          //SBF_chek_2";
          c2=1;  
          n2=0; 
        }


    }
    n3=n1+n2;
    


     cout <<n3<<endl;
     
    if(c1*c2 ){
    
       unsigned int test=frame_UDS[0];
       switch (test){
            case 0X10:
            cout << "your Request is Diagnostic Session Control"<<endl;
            break;
            case 0X11:
            cout << "your Request is ECU Reset"<<endl;
            break;
            case 0X27:
            cout << "your Request is Security Access"<<endl;
            break;
        }
        
        cout<<"Postive_Response_code"<<endl;
        cout<<hex<<frame_UDS[0]+0x40;
        cout <<" ";
        cout<<hex<<frame_UDS[1];
        cout <<endl;
  
        
    }
    else {
        
        switch (n3){
            case 1:
            NRC=0X11;//service not supported
            break;
            case 2:
            NRC=0X12;//Sub Function not supported
            break;
            case 3:
            NRC=0X10;//General Reject
            break;
        }
        cout<<"Negative_Response_code"<<endl;
        cout<<hex<<0x7F;
        cout <<" ";
        cout<<hex<<frame_UDS[1];
        cout <<" ";
        cout <<"NRC N°"<<hex<<NRC;
    }
}

};
int main(){
UDS_Protcole frame;
frame.diagnostic_request();
frame.Display_diagnostic_frame();
frame.diqgnostic_response();
return 0;
}
