#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdbool.h>	    // bool, true, false가 정의된 헤더 파일
#include<Windows.h>		// 윈도우 콘솔창 관련 헤더 파일 


   /////////////////////////////////////////////////
  //              기초프로젝트 8팀                //
 // 팀장 - 이창진   팀원 - 김정아, 고동현, 이영재 //
////////////////////////////////////////////////


// 주문 노드
typedef struct order {
	char menu[20];		// 메뉴 이름
	int count;			// 해당 메뉴 수량
	int price;			// 가격
	int pizza;			// 0이면 일반, 1이면 프리미엄, 2이면 사이드 및 음료
	struct order* next;	//
}order;
order* order_h;			// 주문노드의 맨 앞 노드 (가장 최근에 생성된 노드가 들어감) 


// 사용자 정보 노드
typedef struct user_info{
	char name[20];		// 사용자 이름
	int phone;			// 사용자 전화번호
	int visit;			// 사용자 방문 횟수
	struct order* next;	//
}user_info;
user_info* user_info_h;		    // 사용자 정보 노드의 맨 앞 노드 (가장 최근에 생성된 노드가 들어감) 
user_info* user_info1 = NULL, * user_info2 = NULL, * user_info3 = NULL, * user_info4 = NULL;


// 고객 관리 노드
typedef struct user_manage {
	char name[20];				// 사용자 이름
	int phone;					// 사용자 전화번호
	int visit;					// 사용자 방문 횟수
	struct user_manage* next;	//
}mng;
mng* mng_h;					    // 고객 관리 노드의 맨 앞 노드 (가장 최근에 생성된 노드가 들어감) 


// 테이블 정보 노드
typedef struct table {		
    bool table1;    // True 자리 있음, False 자리 없음
    struct user_info* next1;
    bool table2;
    struct user_info* next2;
    bool table3;
    struct user_info* next3;
    bool table4;
    struct user_info* next4;
}tb;
tb* tb_h;                       // 테이블 노드의 맨 앞 노드 (가장 최근에 생성된 노드가 들어감) 
tb t = { false, NULL, false, NULL, false, NULL, false, NULL };


void program_info();            // 프로그램 정보 출력
void user_menu();               // 사용자 메뉴 출력
void menu_info();               // 가게 메뉴 출력
void input_menu(order* start);  // 메뉴 입력(사용자)
void print_menu(order* start);  // 사용자가 주문한 출력
void new_customer();            // 손님 입장
void middle_bill();		        // 중간 계산 영수증
void last_bill();	            // 최종 영수증


char Premium[4][20] = { "쉬림프피자", "해물피자", "핫스파이스피자", "슈퍼콤비네이션피자" };
char Classic[4][20] = { "불고기피자", "고구마피자",  "포테이토피자",  "페페로니피자" };
/*char price[14][3][20] = { 
    {"불고기피자", "20000", "0"}, {"고구마피자", "19000", "0"}, {"포테이토피자", "19000", "0"}, {"페페로니피자 ", "19000", "0"}, 
    {"쉬림프피자", "26000", "1"}, {"해물피자", "28000", "1"}, {"핫스파이시피자", "24000", "1"}, {"슈퍼콤비네이션피자", "26000", "1"},
    {"윙&봉", "6000", "2"}, {"치킨텐더", "6000", "2"}, {"스파게티", "7000", "2"}, {"치즈볼", "5000", "2"},
    {"콜라", "2000", "2"}, {"사이다", "2000", "2"} 
};*/



int main() {
	SetConsoleTitle(TEXT("Pizza Store - 기초프로젝트 13분반 8조")); // 콘솔창 제목
    
    int num = 0;
    printf("22222");

    order_h = (order*)malloc(sizeof(order));
    user_info_h = NULL;
    mng_h = NULL;
    tb_h = NULL;
    //user_info_h = (user_info*)malloc(sizeof(user_info));
    //mng_h = (mng*)malloc(sizeof(mng));
    //tb_h = (tb*)malloc(sizeof(tb));
    memset(order_h, 0, sizeof(order));

    program_info();

    while (1)
    {
        user_menu();

        // 메뉴 입력시 숫자가 아닌 문자 입력시 버퍼에 입력된 문자 초기화
        if (scanf_s("%d", &num) == 0) {
            system("cls");
            printf("문자를 입력하셨네요. 메뉴는 숫.자.만. 눌러주세요.\n\n");
            rewind(stdin);
        }
        else { // 정상적으로 메뉴를 입력했을 시 switch문 실행
            order* tmp = order_h;
            switch (num) {
                case 1: // 주문
                    for (; tmp->next != NULL;)
                    {
                        tmp = tmp->next;
                    }
                    input_menu(tmp);
                    print_menu(order_h);
                    break;
                case 2: // 주문 수정
                    printf("~ \n");
                    break;
                case 3: // 중간 계산서 출력
                    middle_bill();
                    break;
                case 4: // 계산
                    last_bill();
                    break;
                case 5: // 손님입장
                    new_customer(); 
                    break;
                case 6: return 0; // 종료
                default:
                    system("cls");
                    printf(" 메뉴에 있는 1 ~ 5 사이의 숫.자.만. 누르세요!!!!! \n\n");
                    break;
            }
        }
    }
	return 0;
}


void input_menu(order* start)
{
    system("cls");
    order* current = NULL;

    current = (order*)malloc(sizeof(order));
    start->next = current;
    current->next = NULL;

    menu_info();

    //order memu, count, price 
    printf("\n\n0.프리미엄 피자 1.일반 피자 2.사이드 3.음료\n----------------------------------------------\n메뉴 종류를 입력해주세요. : ");
    scanf_s("%d", &current->pizza);
    getchar();
    printf("\n\n주문하실 메뉴를 적어주세요. : ");
    //scanf_s("%s", current->name);
    gets_s(current->menu, 20);
    printf("개수를 입력해주세요. : ");
    scanf_s("%d", &current->count);
    printf("가격을 입력하시오 : ");
    scanf_s("%d", &current->price);
    printf("");
    // 프리미엄 피자 2판마다 3000 할인, 일반 피자 2판마다 2000 할인
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(Premium[i], current->menu) == 0) // 100s = premium pizza
        {
            current->count *= 100;
            break;
        }
        else if (strcmp(Classic[i], current->menu) == 0) // 1s = classic pizza
        {
            current->count *= 1;
            break;
        }
    }

    int n = current->count / 100; //premium
    int m = current->count % 50;  //classic

    //sale event
    if (n || m)
    {
        n = n / 2;
        m = m / 2;

        current->price -= n * 3000;
        current->price -= m * 2000;
    }
}


void print_menu(order* start){
    system("cls");
    order* tmp = start;
    int i = 0;
    int PPC;
    tmp = tmp->next;
    printf("\n\n주문서 총 목록\n");
    printf("===========================================\n");
    for (i = 0;; i++)
    {
        printf("%d | %s  %d  %d\n\n", i + 1, tmp->menu, tmp->count, tmp->price);

        if (tmp->next == NULL)
            break;
        tmp = tmp->next;
    }
}


void new_customer() {
    int table_count = 0;   // 남은 테이블 수
    int table_number;      // 테이블 번호
    char name[20];         // 사용자의 이름
    int phone;             // 사용자의 전화번호 뒷자리
    int visit;             // 사용자의 방문 횟수
    bool visit_on = false; // user_manage에서 방문 횟수를 가져왔는지 확인하는 변수

    mng* tmp = mng_h;       // 방문 횟수를 가져오기 위한 순회 포인터
    mng* new_user = NULL;   // 새로운 사용자의 정보를 추가하기 위한 포인터

    t.next1 = user_info1; // 각 테이블에 info 포인터 초기화
    t.next2 = user_info2;
    t.next3 = user_info3;
    t.next4 = user_info4;

    printf("현재 남은 테이블은 "); // 남은 테이블 번호를 알려주고 자리가 없으면 종료
    if (t.table1 == false) {
        table_count++;
        printf("1 ");
    }
    if (t.table2 == false) {
        table_count++;
        printf("2 ");
    }
    if (t.table3 == false) {
        table_count++;
        printf("3 ");
    }
    if (t.table4 == false) {
        table_count++;
        printf("4 ");
    }
    if (table_count == 0) {
        printf("없습니다.\n죄송합니다.\n다음에 방문해주세요.");
        return;
    }
    else
        printf("입니다.\n");

    printf("원하시는 테이블을 선택하세요.\n");
    scanf_s("%d", &table_number, sizeof(table_number));
    printf("이름을 입력하세요.\n");
    scanf_s("%s", name, sizeof(name));
    printf("전화번호 뒷자리를 입력하세요.\n");
    scanf_s("%d", &phone, sizeof(phone));

    switch (table_number) {
        case 1:
            t.table1 = true; //앉은 테이블 자리 없음으로 변경
            user_info1 = (user_info*)malloc(sizeof(user_info)); //테이블에 앉은 사용자 정보 입력
            strcpy(user_info1->name, name);
            user_info1->phone = phone;
            user_info1->next = NULL;
            while (tmp != NULL) { //방문 횟수 가져오기
                if (strcmp(tmp->name, name) == 0) {
                    if (tmp->phone == phone) {
                        tmp->visit++;
                        visit = tmp->visit;
                        visit_on = true;
                    }
                }
            }
            if (visit_on == false) { //새로운 사용자면 user_manage에 정보 입력
                new_user = (mng*)malloc(sizeof(mng));
                strcpy(new_user->name, name);
                new_user->phone = phone;
                new_user->visit = 1;
                new_user->next = NULL;
                tmp->next = new_user; //user_manage의 마지막 노드 뒤에 추가(현재 이부분 오류 있음)
            }
            break;
        case 2:
            t.table2 = true; //앉은 테이블 자리 없음으로 변경
            user_info2 = (user_info*)malloc(sizeof(user_info)); //테이블에 앉은 사용자 정보 입력
            strcpy(user_info2->name, name);
            user_info2->phone = phone;
            user_info2->next = NULL;
            while (tmp != NULL) { //방문 횟수 가져오기
                if (strcmp(tmp->name, name) == 0) {
                    if (tmp->phone == phone) {
                        tmp->visit++;
                        visit = tmp->visit;
                        visit_on = true;
                    }
                }
            }
            if (visit_on == false) { //새로운 사용자면 user_manage에 정보 입력
                new_user = (mng*)malloc(sizeof(mng));
                strcpy(new_user->name, name);
                new_user->phone = phone;
                new_user->visit = 1;
                new_user->next = NULL;
                tmp->next = new_user; //user_manage의 마지막 노드 뒤에 추가
            }
            break;
        case 3:
            t.table3 = true; //앉은 테이블 자리 없음으로 변경
            user_info3 = (user_info*)malloc(sizeof(user_info)); //테이블에 앉은 사용자 정보 입력
            strcpy(user_info3->name, name);
            user_info3->phone = phone;
            user_info3->next = NULL;
            while (tmp != NULL) { //방문 횟수 가져오기
                if (strcmp(tmp->name, name) == 0) {
                    if (tmp->phone == phone) {
                        tmp->visit++;
                        visit = tmp->visit;
                        visit_on = true;
                    }
                }
            }
            if (visit_on == false) { //새로운 사용자면 user_manage에 정보 입력
                new_user = (mng*)malloc(sizeof(mng));
                strcpy(new_user->name, name);
                new_user->phone = phone;
                new_user->visit = 1;
                new_user->next = NULL;
                tmp->next = new_user; //user_manage의 마지막 노드 뒤에 추가
            }
            break;
        case 4:
            t.table4 = true; //앉은 테이블 자리 없음으로 변경
            user_info4 = (user_info*)malloc(sizeof(user_info)); //테이블에 앉은 사용자 정보 입력
            strcpy(user_info4->name, name);
            user_info4->phone = phone;
            user_info4->next = NULL;
            while (tmp != NULL) { //방문 횟수 가져오기
                if (strcmp(tmp->name, name) == 0) {
                    if (tmp->phone == phone) {
                        tmp->visit++;
                        visit = tmp->visit;
                        visit_on = true;
                    }
                }
            }
            if (visit_on == false) { //새로운 사용자면 user_manage에 정보 입력
                new_user = (mng*)malloc(sizeof(mng));
                strcpy(new_user->name, name);
                new_user->phone = phone;
                new_user->visit = 1;
                new_user->next = NULL;
                tmp->next = new_user; //user_manage의 마지막 노드 뒤에 추가
            }
            break;
    }
}


void middle_bill() {
    int table_num;              // 테이블 번호
    int sum = 0;                // 총가격
    int event_pizza_p = 0;      // 프리미엄 피자 할인금액
    int pizza_p_count = 0;      // 프리미엄 피자 개수, 이벤트 개수 
    int event_pizza_c = 0;      // 일반 피자 할인금액
    int pizza_c_count = 0;      // 일반 피자 개수, 이벤트 개수
    int first_order = 0;        // 첫 주문 할인 금액
    int five_order = 0;         // 5번 주문 할인 금액
    int event = 0;              // 총 할인금액

    user_info* tmp = user_info_h;         // user 사용자 정보 저장
    mng* who = mng_h;           // 저장된 user 정보
    order* list = order_h;      // order 주문메뉴 읽어오는 역할

    // 중간 영수증 테이블 선택
    printf("사용하신 테이블 번호를 입력해주세요 : ");
    scanf_s("%d", &table_num);

    switch (table_num) {
        case 1:
            if (tb_h->table1 == 0) {
                printf("현재 자리가 비어있는 테이블입니다.\n");
                return 0;
            }
            tmp = tb_h->next1;  // 사용자 정보 tmp
            list = tmp->next;   // 주문 메뉴 
            order_h = list;  // 주문 메뉴(head)
            break;
        case 2:
            if (tb_h->table2 == 0) {
                printf("현재 자리가 비어있는 테이블입니다.\n");
                return 0;
            }
            tmp = tb_h->next2;
            list = tmp->next;
            order_h = list;
            break;
        case 3:
            if (tb_h->table3 == 0) {
                printf("현재 자리가 비어있는 테이블입니다.\n");
                return 0;
            }
            tmp = tb_h->next3;
            list = tmp->next;
            order_h = list;
            break;
        case 4:
            if (tb_h->table4 == 0) {
                printf("현재 자리가 비어있는 테이블입니다.\n");
                return 0;
            }
            tmp = tb_h->next4;
            list = tmp->next;
            order_h = list;
            break;
    }

    // 주문내용(영수증)
    printf("\t\t중간 영수증 출력\n");
    printf("---------------------------------------------------\n");
    while (list->next != NULL) {
        printf("%s\t\t%d\t%d원\n", list->menu, list->count, list->price);
        if (list->pizza == 0)  pizza_c_count++;       // 일반피자 개수
        else if (list->pizza == 1) pizza_p_count++;   // 프리미엄 피자 개수
        list = list->next;
    }

    // 할인 이벤트(영수증)
    printf("---------------------------------------------------\n");
    while (who->next != NULL) {
        if ((strcmp(tmp->name, who->name) == 0) && (tmp->phone == who->phone)) {
            // 첫주문 이벤트
            if (who->visit == 1) {
                first_order = 3000;
                printf("첫 방문 할인 이벤트\t\t%d\n", first_order);
            }
            // 5번 방문 이벤트
            if (who->visit == 5) {
                five_order = 5000;
                printf("5번 방문 할인 이벤트\t\t%d\n", five_order);
            }
            break;
        }
        who = who->next;
    }

    // 일반피자 할인 이벤트
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // 이벤트 개수
        event_pizza_c = (pizza_c_count * 2000);
        printf("일반피자 2판 주문 할인 이벤트\t%d\t%d\n", pizza_c_count, event_pizza_c);
    }

    // 프리미엄 피자 할인 이벤트
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // 이벤트 개수
        event_pizza_p = (pizza_p_count * 3000);
        printf("일반피자 2판 주문 할인 이벤트\t%d\t%d\n", pizza_p_count, event_pizza_p);
    }

    // 총가격(영수증)
    printf("---------------------------------------------------");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("결제금액\t\t\t%d\n", sum);
    return 1;
}


void last_bill() {
    int pay;
    int table_num;              // 테이블 번호
    int sum = 0;                // 총가격
    int event_pizza_p = 0;      // 프리미엄 피자 할인금액
    int pizza_p_count = 0;      // 프리미엄 피자 개수, 이벤트 개수 
    int event_pizza_c = 0;      // 일반 피자 할인금액
    int pizza_c_count = 0;      // 일반 피자 개수, 이벤트 개수
    int first_order = 0;        // 첫 주문 할인 금액
    int five_order = 0;         // 5번 주문 할인 금액
    int event = 0;              // 총 할인금액

    user_info* tmp = user_info_h;         // user 사용자 정보 저장
    mng* who = mng_h;           // 저장된 user 정보
    order* list = order_h;      // order 주문메뉴 읽어오는 역할
    order* pre;                 // free(주문메뉴)

    // 중간 영수증 테이블 선택
    printf("사용하신 테이블 번호를 입력해주세요 : ");
    scanf_s("%d", &table_num);
    switch (table_num) {
    case 1:
        if (tb_h->table1 == 0) {
            printf("현재 자리가 비어있는 테이블입니다.\n");
            return 0;
        }
        tmp = tb_h->next1;  // 사용자 정보 tmp
        list = tmp->next;   // 주문 메뉴 
        order_h = list;  // 주문 메뉴(head)
        break;
    case 2:
        if (tb_h->table2 == 0) {
            printf("현재 자리가 비어있는 테이블입니다.\n");
            return 0;
        }
        tmp = tb_h->next2;
        list = tmp->next;
        order_h = list;
        break;
    case 3:
        if (tb_h->table3 == 0) {
            printf("현재 자리가 비어있는 테이블입니다.\n");
            return 0;
        }
        tmp = tb_h->next3;
        list = tmp->next;
        order_h = list;
        break;
    case 4:
        if (tb_h->table4 == 0) {
            printf("현재 자리가 비어있는 테이블입니다.\n");
            return 0;
        }
        tmp = tb_h->next4;
        list = tmp->next;
        order_h = list;
        break;
    }

    // 주문내용(영수증)
    printf("\t\t중간 영수증 출력\n");
    printf("---------------------------------------------------\n");
    while (list->next != NULL) {
        printf("%s\t\t%d\t%d원\n", list->menu, list->count, list->price);
        if (list->pizza == 0)  pizza_c_count++;     // 일반피자 개수
        else if (list->pizza == 1) pizza_p_count++; // 프리미엄 피자 개수
        list = list->next;
    }
    // 할인 이벤트(영수증)
    printf("---------------------------------------------------\n");
    while (who->next != NULL) {
        if ((strcmp(tmp->name, who->name) == 0) && (tmp->phone == who->phone)) {
            // 첫주문 이벤트
            if (who->visit == 1) {
                first_order = 3000;
                printf("첫 방문 할인 이벤트\t\t%d\n", first_order);
            }
            // 5번 방문 이벤트
            if (who->visit == 5) {
                five_order = 5000;
                printf("5번 방문 할인 이벤트\t\t%d\n", five_order);
            }
            break;
        }
        who = who->next;
    }

    // 일반피자 할인 이벤트
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // 이벤트 개수
        event_pizza_c = (pizza_c_count * 2000);
        printf("일반피자 2판 주문 할인 이벤트\t%d\t%d\n", pizza_c_count, event_pizza_c);
    }

    // 프리미엄 피자 할인 이벤트
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // 이벤트 개수
        event_pizza_p = (pizza_p_count * 3000);
        printf("일반피자 2판 주문 할인 이벤트\t%d\t%d\n", pizza_p_count, event_pizza_p);
    }

    // 총가격(영수증)
    printf("---------------------------------------------------");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("결제금액\t\t\t%d\n", sum);
    return sum;

    printf("총금액은  %d원 입니다.\n", sum);
    printf("결제 금액을 입력해주세요 : ");
    scanf_s("%d", &pay);
    if (sum == pay) {
        printf("결제가 완료되었습니다.\n");
        // 테이블 연결 끊기
        list = tmp->next;
        switch (table_num) {
            case 1:
                tb_h->next1 = NULL; // 테이블 연결 끊기
                tb_h->table1 = 0;   // 테이블 자리 비우기
                free(tmp);          // 유저 free
                while (list->next != NULL) {
                    pre = list;
                    free(pre);
                    list = list->next;
                }
                break;
            case 2:
                tb_h->next2 = NULL;
                tb_h->table2 = 0;
                free(tmp);
                while (list->next != NULL) {
                    pre = list;
                    free(pre);
                    list = list->next;
                }
                break;
            case 3:
                tb_h->next3 = NULL;
                tb_h->table3 = 0;
                free(tmp);
                while (list->next != NULL) {
                    pre = list;
                    free(pre);
                    list = list->next;
                }
                break;
            case 4:
                tb_h->next4 = NULL;
                tb_h->table4 = 0;
                free(tmp);
                while (list->next != NULL) {
                    pre = list;
                    free(pre);
                    list = list->next;
                }
                break;
        }
        return 1;
    }
    else if (sum > pay) {
        printf("결제금액이 부족합니다. 다시 결제해주세요\n");
        return 0;
    }
    else {
        printf("총금액을 초과하였습니다. 다시 결제해주세요\n");
        return 0;
    }
}


void user_menu() {
    printf("=============================================================\n");
    printf("\t\t\t반갑습니다 손님 ~ :)\n"); 
    printf("새로 들어온 손님은 5번 메뉴인 '손님입장' 메뉴를 선택해주세요.\n");
    printf("=============================================================\n\n");
    printf("\t\t1. 주문\n");
    printf("\t\t2. 주문 수정\n");
    printf("\t\t3. 중간 계산서 출력\n");
    printf("\t\t4. 계산\n");
    printf("\t\t5. 손님입장\n");
    printf("\t\t6. 종료\n");
    printf("\n=============================================================\n\n");
    printf("메뉴를 입력하세요 : ");
}


void menu_info()
{
    system("cls");
    printf("\n\t\t          [메뉴판]           \n");
    printf("\t\t        프리미엄 피자        \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t쉬림프 피자          26,000  \n");
    printf("\t\t해물 피자            28,000  \n");
    printf("\t\t핫스파이시 피자      24,000  \n");
    printf("\t\t슈퍼콤비네이션 피자  26,000  \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t          일반 피자          \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t불고기 피자          20,000  \n");
    printf("\t\t고구마 피자          19,000  \n");
    printf("\t\t포테이토 피자        19,000  \n");
    printf("\t\t페퍼로니 피자        19,000  \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t           사이드            \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t윙&봉(6조각)          6,000  \n");
    printf("\t\t치킨텐더(6조각)       6,000  \n");
    printf("\t\t스파게티              7,000  \n");
    printf("\t\t치즈볼                5,000  \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t            음료             \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t콜라                  2,000  \n");
    printf("\t\t사이다                2,000  \n");
    printf("\t\t-----------------------------\n\n");
}


void program_info()
{
    printf("\n\t------------------------------------------------\n");
    printf("\t               피자 가게  프로그램              \n");
    printf("\t   8팀 : 이창진(조장), 고동현, 김정아, 이영재   \n");
    printf("\t------------------------------------------------\n\n\n");
}