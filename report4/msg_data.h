struct real_data{
        short num; // 랜덤으로 정수를 생성하여 저장할 short형 변수
        char answer1[50]; // 정답 구문을 저장할 문자열
        char answer2[50]; // 오답 구문을 저장할 문자열
};
struct message{
        long msg_type; // 메세지의 유형(type)을 담는 long형 변수
        struct real_data data; // 위의 구조체를 member로 가지는 변수
};
