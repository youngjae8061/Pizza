#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
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
	int pizza;			// 0이면 일반, 1이면 프리미엄, 3이면 사이드 및 음료
	struct order* next;	//
}order;
order* order_h;			// 주문노드의 맨 앞 노드 (가장 최근에 생성된 노드가 들어감) 

// 사용자 정보 노드
typedef struct user_info{
	char name[20];		// 사용자 이름
	int phone;			// 사용자 전화번호
	int visit;			// 사용자 방문 횟수
	struct order* next;	//
}info;
info* info_h;		    // 사용자 정보 노드의 맨 앞 노드 (가장 최근에 생성된 노드가 들어감) 

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
	// bool table;				// True 자리 있음, False 자리 없음
    int table1;
    struct user_info* next1;
    int table2;
    struct user_info* next2;
    int table3;
    struct user_info* next3;
    int table4;
    struct user_info* next4;

}tb;
tb* tb_h;				    // 주문노드의 맨 앞 노드 (가장 최근에 생성된 노드가 들어감) 


void program_info();            // 프로그램 정보 출력
void user_menu();               // 사용자 메뉴 출력
void menu_info();               // 가게 메뉴 출력
void input_menu();              // 메뉴 입력(사용자)
void middle_bill();		        // 중간 계산 영수증
void last_bill();		        // 최종 영수증


int main() {
	SetConsoleTitle(TEXT("Pizza Store - 기초프로젝트 13분반 8조")); // 콘솔창 제목

    int num = 0;
    order* head = NULL;
    head = (order*)malloc(sizeof(order));
    head->next = NULL;

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
            switch (num) {
                case 1: // 주문
                    printf("주문하기를 선택하셨습니다. \n");
                    menu_info();
                    input_menu();
                    break;
                case 2: // 주문 수정
                    printf("~ \n");
                    break;
                case 3: // 중간 계산서 출력
                    printf("~ \n");
                    break;
                case 4: // 계산
                    printf("~ \n");
                    break;
                case 5: return 0; // 종료
                default:
                    system("cls");
                    printf(" 메뉴에 있는 1 ~ 5 사이의 숫.자.만. 누르세요!!!!! \n\n");
                    break;
            }
        }
    }

	return 0;
}


void program_info()
{
    printf("------------------------------------------------\n");
    printf("               피자 가게  프로그램              \n");
    printf("   8팀 : 이창진(조장), 고동현, 김정아, 이영재   \n");
    printf("------------------------------------------------\n\n\n");
}


void menu_info()
{
    printf("          [메뉴판]           \n");
    printf("        프리미엄 피자        \n");
    printf("-----------------------------\n");
    printf("쉬림프 피자          26,000  \n");
    printf("해물 피자            28,000  \n");
    printf("핫스파이시 피자      24,000  \n");
    printf("슈퍼콤비네이션 피자  26,000  \n");
    printf("-----------------------------\n");
    printf("          일반 피자          \n");
    printf("-----------------------------\n");
    printf("불고기 피자          20,000  \n");
    printf("고구마 피자          19,000  \n");
    printf("포테이포 피자        19,000  \n");
    printf("페페로니 피자        19,000  \n");
    printf("-----------------------------\n");
    printf("           사이드            \n");
    printf("-----------------------------\n");
    printf("윙&봉(6조각)          6,000  \n");
    printf("치킨텐더(6조각)       6,000  \n");
    printf("스파게티              7,000  \n");
    printf("치즈볼                5,000  \n");
    printf("-----------------------------\n");
    printf("            음료             \n");
    printf("-----------------------------\n");
    printf("콜라                  2,000  \n");
    printf("사이다                2,000  \n");
    printf("-----------------------------\n");

}


void input_menu()
{
    order* curr = NULL;
    order* end = NULL;
    curr = (order*)malloc(sizeof(order));
    curr->next = NULL;

    printf("?\n");
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

    info* tmp = info_h;         // user 사용자 정보 저장
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

    info* tmp = info_h;         // user 사용자 정보 저장
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
    printf("===========================\n");
    printf("반갑습니다 손님.\n메뉴를 선택해주세요 :)\n");
    printf("===========================\n");
    printf("1. 주문\n");
    printf("2. 주문 수정\n");
    printf("3. 중간 계산서 출력\n");
    printf("4. 계산\n");
    printf("5. 종료\n");
    printf("===========================\n\n");
    printf("메뉴를 입력하세요 : ");
}