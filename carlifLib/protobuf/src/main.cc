

#include <stdio.h>
#include <string>

#include "Message.pb.h"
#include "Message1.pb.h"

int main(){
	
//	for (int m = 0; m < 10000 * 10000; m++){
		Message1* msg1 = new Message1;
		Message* msg = msg1->add_msgs();
		msg->set_str("a");
		msg->set_value(1);

		Message* msg2 = msg1->add_msgs();
		msg2->set_str("b");
		msg2->set_value(2);

		std::string str = msg1->SerializeAsString();
		fprintf(stderr, "the str size is:%d\n", str.size());

		Message1* msg3 = new Message1;
		bool isok = msg3->ParseFromString(str);
		if (!isok){
			delete msg1;
			fprintf(stderr, "error to parse!\n");
			return 0;
		}

		int s = msg3->msgs_size();
		for (int j = 0; j < s; j++){
			const Message& m = msg3->msgs(j);
			fprintf(stderr, "the str %s\n", m.str().c_str());
			fprintf(stderr, "the value is %d\n", m.value());
		}

		delete msg1;
		delete msg3;

//	}
	return 0;
}
