#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctype.h>
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


// 사용자 정보 노드
typedef struct user_info {
    char name[20];		// 사용자 이름
    int phone;			// 사용자 전화번호
    int visit;			// 사용자 방문 횟수
    struct order* next;	//
}user_info;
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
tb t = { false, NULL, false, NULL, false, NULL, false, NULL };


void program_info();            // 프로그램 정보 출력
void user_menu();               // 사용자 메뉴 출력
void menu_info();               // 가게 메뉴 출력
void input_menu();              // 메뉴 입력(사용자)
void modify_menu();             // 주문한 메뉴 수정
void modify_bot(order* find);   // 실제로 메뉴 수정하는 함수
void empty_table();             // 비어있는 테이블
void invalid_table();           // 테이블을 잘못입력한 경우
void new_customer();            // 손님 입장
void middle_bill();		        // 중간 계산 영수증
void last_bill();	            // 최종 영수증


char menu_price[14][3][20] = {
    {"불고기피자", "20000", "0"}, {"고구마피자", "19000", "0"}, {"포테이토피자", "19000", "0"}, {"페퍼로니피자 ", "19000", "0"},
    {"쉬림프피자", "26000", "1"}, {"해물피자", "28000", "1"}, {"핫스파이시피자", "24000", "1"}, {"슈퍼콤비네이션피자", "26000", "1"},
    {"윙&봉", "6000", "2"}, {"치킨텐더", "6000", "2"}, {"스파게티", "7000", "2"}, {"치즈볼", "5000", "2"},
    {"콜라", "2000", "2"}, {"사이다", "2000", "2"}
};


int main() {
    SetConsoleTitle(TEXT("Pizza Store - 기초프로젝트 13분반 8조")); // 콘솔창 제목
    system("mode con:cols=150 lines=70");

    int num = 0;
    mng_h = (mng*)malloc(sizeof(mng)); // mng_h 값 초기화
    strcpy(mng_h->name, "초기화");
    mng_h->phone = 0;
    mng_h->visit = 0;
    mng_h->next = NULL;

    program_info();

    while (1)
    {
        user_menu();
        rewind(stdin);

        // 메뉴 입력시 숫자가 아닌 문자 입력시 버퍼에 입력된 문자 초기화
        if (scanf_s("%d", &num) == 0) {
            system("cls");
            printf(" 문자를 입력하셨네요. 메뉴는 숫.자.만. 눌러주세요.\n\n");
        }
        else { // 정상적으로 메뉴를 입력했을 시 switch문 실행
            switch (num) {
            case 1: // 주문
                input_menu();
                break;
            case 2: // 주문 수정
                modify_menu();
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


void modify_menu() {
    system("cls");
    int t_num = 0;    // 테이블 번호 선택
    int select = 0;   // 메뉴 선택

    order* find;

    printf("앉은 테이블을 입력하세요. ");
    scanf_s("%d", &t_num) == 0;
    // 정상적으로 메뉴를 입력했을 시 switch문 실행
    switch (t_num) {
    case 1:
        if (t.table1 == false) {
            empty_table();
            return 0;
        }
        find = t.next1->next;
        modify_bot(find);
        break;
    case 2:
        if (t.table2 == false) {
            empty_table();
            return 0;
        }
        find = t.next2->next;
        modify_bot(find);
        break;
    case 3:
        if (t.table3 == false) {
            empty_table();
            return 0;
        }
        find = t.next3->next;
        modify_bot(find);
        break;
    case 4:
        if (t.table4 == false) {
            empty_table();;
            return 0;
        }
        find = t.next4->next;
        modify_bot(find);
        break;
    default:
        invalid_table();
        return 0;
    }
}


void modify_bot(order* find) {
    system("cls");
    int temp_count = 0; // 수량 변경 임시 저장(0인지 구분)
    char modify[20];        // 변경할 메뉴의 이름
    int select;
    order* head;    // 헤더 노드
    order* temp;    // 수량 변경 후 노드 삭제하기 위한 노드

    head = find;
    temp = NULL;

    while (1) {
        printf("\n======================================\n");
        printf("메뉴를 선택해주세요\n");
        printf("1. 메뉴 수정하기 (초기화면으로 돌아가려면 1을 제외한 아무키나 눌러주세요.) : ");
        scanf_s("%d", &select);
        if (select == 1) {
            printf("\n\n메뉴명을 입력해주세요 : ");
            scanf_s("%s", modify, sizeof(modify));
            while (1) { // 해당 메뉴 찾기 시작
                // 수정하기 위해 입력 받은 modify가 find의 menu에 없을 경우
                if (!(strcmp(modify, find->menu) == 0) && find->next == NULL) {
                    printf("\n ============================= 그런 메뉴는 없습니다!! =========================\n\n");
                    return 0;
                }
                // 수정하기 위해 입력 받은 modify와 find의 menu가 같은 문자일 경우
                if (strcmp(modify, find->menu) == 0) {
                    printf("수량을 변경해주세요 : ");
                    scanf_s("%d", &temp_count);
                    if (temp_count == 0) { // 수량이 0일때 해당 노드 삭제 + 앞뒤 노드 이어주기
                        while (1) { // 수량이 0으로 변경되어 해당 노드 free() + 앞뒤 노드 이어주기
                                // modify과 head의 menu가 같은경우 즉, 맨앞의 노드를 삭제할 경우
                            if (strcmp(modify, head->menu) == 0) {
                                head = find->next;
                            }
                            // find의 다음 노드가 NULL인 경우 즉, 맨 마지막 노드를 삭제할 경우
                            else if (find->next == NULL) {
                                temp->next = NULL;
                            }
                            // 그 외의 경우
                            else {
                                temp->next = find->next;
                            }
                            free(find);
                            break;
                            // 해당 문자를 찾기위해 다음 노드로 이동
                            temp = find;
                            find = find->next;
                        }
                        printf("삭제 했습니다!!!\n\n");
                        break;
                    }
                    // 0말고 다른 수량으로 변경될때 
                    find->count = temp_count;
                    for (int i = 0; i < 14; i++) {
                        if (strcmp(find->menu, menu_price[i][0]) == 0)
                            find->price = atoi(menu_price[i][1]) * temp_count;
                    }
                    system("cls");
                    printf("수정 성공했어요!\n");  // 수량 변경 성공
                    break;
                }
                find = find->next; // 해당 메뉴 없을 시 다음 노드로 이동
            }
        }
        else { // 이전화면으로 돌아가기(2)를 눌렀을 때
            return 0;
        }
    }
}


void empty_table() {
    system("cls");
    printf("해당 테이블은 비어있습니다.\n");
    printf("\n만일, 처음 입장 시 테이블을 선택하지 않으셨다면 '5. 손님입장' 메뉴를 통해 테이블을 먼저 선택 해주세요\n\n");
}


void invalid_table(){
    system("cls");
    printf("\n매장 내에 테이블은 1, 2, 3, 4번 테이블로 총 4개 입니다. 테이블 번호를 확인해 주세요\n");
    printf("\n만일, 처음 입장 시 테이블을 선택하지 않으셨다면 '5. 손님입장' 메뉴를 통해 테이블을 먼저 선택 해주세요\n\n");
}


void input_menu() {
    system("cls");
    menu_info();
    int table_number; // 앉은 테이블 번호
    char menu[20]; //메뉴
    int count; //메뉴의 수량
    int select;
    bool check;
    bool input = false;
    order* tmp = NULL; //주문 노드의 헤드(테이블 -> 유저정보 -> tmp)
    order* pre = NULL; //주문 노드의 마지막을 가리키는 포인터
    user_info* user_info = NULL;

    printf("앉은 테이블을 입력하세요. : ");
    //scanf_s("%d", &table_number);
    if (scanf_s("%d", &table_number) == 0) {
        system("cls");
        printf(" 문자를 입력하셨네요. 매장엔 1~4번 테이블만 있습니다. 않으신 손님의 테이블 번호를 눌러주세요.\n\n");
        return;
    }
    else {
        switch (table_number) {
        case 1:
            if (t.table1 == false) {
                empty_table();
                return;
            }
            tmp = t.next1->next; //주문 노드의 헤드(테이블 -> 유저정보 -> tmp)
            user_info = t.next1;
            break;
        case 2:
            if (t.table2 == false) {
                empty_table();
                return;
            }
            tmp = t.next2->next; //주문 노드의 헤드(테이블 -> 유저정보 -> tmp)
            user_info = t.next2;
            break;
        case 3:
            if (t.table3 == false) {
                empty_table();
                return;
            }
            tmp = t.next3->next; //주문 노드의 헤드(테이블 -> 유저정보 -> tmp)
            user_info = t.next3;
            break;
        case 4:
            if (t.table4 == false) {
                empty_table();
                return;
            }
            tmp = t.next4->next; //주문 노드의 헤드(테이블 -> 유저정보 -> tmp)
            user_info = t.next4;
            break;
        default:
            invalid_table();
            return 0;
        }
    }

    while (1) {
        check = false;

        printf("\n======================================\n");
        printf(">>> 메뉴를 선택해주세요\n");
        printf(">>> 1. 주문하기 \n>>> 초기화면으로 돌아가려면 1을 제외한 아무키나 눌러주세요. : ");

        if (scanf_s("%d", &select) == 0) {
            system("cls");
            printf("\n이전 메뉴로 돌아가기를 선택하셨습니다.\n\n");
            return;
        }
        else {
            if (select == 1) {
                printf("주문하실 메뉴를 입력해주세요. : ");
                scanf_s("%s", menu, sizeof(menu));
                for (int i = 0; i < 14; i++) {
                    if (strcmp(menu_price[i][0], menu) == 0) { //메뉴판에 있는 메뉴면 실행
                        printf("개수를 입력해주세요. : ");
                        scanf_s("%d", &count);

                        if (tmp == NULL) { // 첫 주문
                            tmp = (order*)malloc(sizeof(order));
                            strcpy(tmp->menu, menu);
                            tmp->count = count;
                            tmp->price = atoi(menu_price[i][1]) * count;
                            tmp->pizza = atoi(menu_price[i][2]);
                            tmp->next = NULL;
                            user_info->next = tmp;
                            break;
                        }

                        while (tmp != NULL) { // 첫 주문이 아니면 같은 메뉴를 주문 했는지 찾기
                            if (strcmp(tmp->menu, menu) == 0) {
                                tmp->count += count;
                                tmp->price = atoi(menu_price[i][1]) * tmp->count;
                                input = true;
                                break;
                            }
                            pre = tmp;
                            tmp = tmp->next;
                        }
                        if (input == true)
                            break;
                        tmp = (order*)malloc(sizeof(order)); //같은 메뉴가 없다면 노드 마지막에 추가
                        pre->next = tmp;
                        strcpy(tmp->menu, menu);
                        tmp->count = count;
                        tmp->price = atoi(menu_price[i][1]) * count;
                        tmp->pizza = atoi(menu_price[i][2]);
                        tmp->next = NULL;
                        check = true;
                    }
                    if (check == false && i == 13)
                        printf("메뉴명을 다시 확인하고 정확히 주문해주세요.\n");
                }
            }
            else {
                system("cls");
                printf("\n이전 메뉴로 돌아가기를 선택하셨습니다.\n\n");
                return;
            }
        }
    }
}


void new_customer() {
    system("cls");
    int table_count = 0;// 남은 테이블 수
    int table_number;   // 테이블 번호
    char name[20];      // 사용자의 이름
    int phone;          // 사용자의 전화번호 뒷자리
    int visit;          // 사용자의 방문 횟수
    mng* tmp = mng_h;   // 방문 횟수를 가져오기 위한 순회 포인터
    mng* pre = mng_h;   // 마지막 노드를 가리키는 포인터
    mng* new_user = NULL; // 새로운 사용자의 정보를 추가하기 위한 포인터
    user_info* ui;
    printf("현재 남은 테이블은 [  "); //남은 테이블 번호를 알려주고 자리가 없으면 종료
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
        printf("0  ] 입니다.\n자리가 없으니 다음에 방문해주세요.\n\n");
        return;
    }
    else
        printf(" ] 입니다.\n");

    rewind(stdin);

    printf("원하시는 테이블을 선택하세요 : ");
    scanf_s("%d", &table_number);

    switch (table_number) {
    case 1:
        if (t.table1 == true) {
            printf("\n선택하신 테이블은 이미 선택된 테이블입니다. 다른 테이블을 선택해주세요. \n\n");
            return;
        }
        t.table1 = true; //앉은 테이블 자리 없음으로 변경
        user_info1 = (user_info*)malloc(sizeof(user_info)); //테이블에 앉은 사용자 정보 입력
        ui = user_info1;
        t.next1 = ui;
        break;
    case 2:
        if (t.table2 == true) {
            printf("\n선택하신 테이블은 이미 선택된 테이블입니다. 다른 테이블을 선택해주세요. \n\n");
            return;
        }
        t.table2 = true; //앉은 테이블 자리 없음으로 변경
        user_info2 = (user_info*)malloc(sizeof(user_info)); //테이블에 앉은 사용자 정보 입력
        ui = user_info2;
        t.next2 = ui;
        break;
    case 3:
        if (t.table3 == true) {
            printf("\n선택하신 테이블은 이미 선택된 테이블입니다. 다른 테이블을 선택해주세요. \n\n");
            return;
        }
        t.table3 = true; //앉은 테이블 자리 없음으로 변경
        user_info3 = (user_info*)malloc(sizeof(user_info)); //테이블에 앉은 사용자 정보 입력
        ui = user_info3;
        t.next3 = ui;
        break;
    case 4:
        if (t.table4 == true) {
            printf("\n선택하신 테이블은 이미 선택된 테이블입니다. 다른 테이블을 선택해주세요. \n\n");
            return;
        }
        t.table4 = true; //앉은 테이블 자리 없음으로 변경
        user_info4 = (user_info*)malloc(sizeof(user_info)); //테이블에 앉은 사용자 정보 입력
        ui = user_info4;
        t.next4 = ui;
        break;
    default:
        system("cls");
        printf("\n매장 내에 테이블은 1, 2, 3, 4번 테이블로 총 4개 입니다. 테이블 번호를 확인해 주세요\n");
        return;
    }

    rewind(stdin);

    printf("이름을 입력하세요 : ");
    scanf_s("%s", name, sizeof(name));

    rewind(stdin);

    printf("전화번호 뒷자리를 입력하세요 : ");
    if (scanf_s("%d", &phone) == 0 || phone - 1000 < 0 || 10000 - phone < 1) {
        system("cls");
        printf("문자를 입력했거나. 4자리를 입력하지 않으셨습니다. 전화번호 뒷자리는 숫.자.4.자.리.로 입력하세요. \n\n");
        switch (table_number) {
        case 1: t.table1 = false;
            break;
        case 2: t.table2 = false;
            break;
        case 3: t.table3 = false;
            break;
        case 4: t.table4 = false;
            break;
        default: break;
        }
        return;
    }
    strcpy(ui->name, name);

    ui->phone = phone;
    ui->visit = 1;
    ui->next = NULL;

    while (tmp != NULL) { //방문 횟수 가져오기
        if (strcmp(tmp->name, name) == 0) {
            if (tmp->phone == phone) {
                tmp->visit++;
                visit = tmp->visit;
                ui->visit = visit;
                return;
            }
        }
        pre = tmp;
        tmp = tmp->next;
    }

    new_user = (mng*)malloc(sizeof(mng));//새로운 사용자면 user_manage에 정보 입력
    strcpy(new_user->name, name);
    new_user->phone = phone;
    new_user->visit = 1;
    new_user->next = NULL;
    pre->next = new_user; //user_manage의 마지막 노드 뒤에 추가

    system("cls");
}


void middle_bill() {
    system("cls");
    int table_num;              // 테이블 번호
    int sum = 0;                // 총가격
    int event_pizza_p = 0;      // 프리미엄 피자 할인금액
    int pizza_p_count = 0;      // 프리미엄 피자 개수, 이벤트 개수 
    int event_pizza_c = 0;      // 일반 피자 할인금액
    int pizza_c_count = 0;      // 일반 피자 개수, 이벤트 개수
    int first_order = 0;        // 첫 주문 할인 금액
    int five_order = 0;         // 5번 주문 할인 금액
    int event = 0;              // 총 할인금액

    order* tmp = NULL;
    user_info* user_info = NULL;

    // 중간 영수증 테이블 선택
    printf("앉은 테이블을 입력하세요. ");
    scanf_s("%d", &table_num, sizeof(table_num));

    switch (table_num) {
    case 1:
        if (t.table1 == false) {
            empty_table();
            return 0;
        }
        tmp = t.next1->next;
        user_info = t.next1;
        break;
    case 2:
        if (t.table2 == 0) {
            empty_table();
            return 0;
        }
        tmp = t.next2->next;
        user_info = t.next2;
        break;
    case 3:
        if (t.table3 == 0) {
            empty_table();
            return 0;
        }
        tmp = t.next3->next;
        user_info = t.next3;
        break;
    case 4:
        if (t.table4 == 0) {
            empty_table();
            return 0;
        }
        tmp = t.next4->next;
        user_info = t.next4;
        break;
    default:
        invalid_table();
        return;
        break;
    }

    // 주문내용(영수증)
    printf("\n\n\t\t중간 영수증 출력\n");
    printf("---------------------------------------------------\n");
    if (tmp == NULL) {
        printf("아직 주문한 메뉴가 없습니다.\n");
        printf("---------------------------------------------------\n\n");
        return;
    }
    while (tmp != NULL) {
        printf("%20s\t%d\t%d원\n", tmp->menu, tmp->count, tmp->price);
        sum += tmp->price;
        if (tmp->pizza == 0)
            pizza_c_count = tmp->count;
        else if (tmp->pizza == 1)
            pizza_p_count = tmp->count;
        tmp = tmp->next;
    }

    // 할인 이벤트(영수증)
    printf("---------------------------------------------------\n");
    if (user_info->visit == 1) {
        first_order = 3000;
        printf("첫 방문 할인 이벤트\t\t%d\n", first_order);
    }
    if (user_info->visit == 5) {
        five_order = 5000;
        printf("5번 방문 할인 이벤트\t\t%d원\n", five_order);
    }

    // 일반피자 할인 이벤트
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // 이벤트 개수
        event_pizza_c = (pizza_c_count * 2000);
        printf("일반피자 2판 주문 할인 이벤트  \t%d\t%d원\n", pizza_c_count, event_pizza_c);
    }

    // 프리미엄 피자 할인 이벤트
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // 이벤트 개수
        event_pizza_p = (pizza_p_count * 3000);
        printf("프리미엄피자 2판 주문 할인 이벤트\t%d\t%d원\n", pizza_p_count, event_pizza_p);
    }

    // 총가격(영수증)
    printf("---------------------------------------------------\n");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("결제금액\t\t\t\t%d원\n\n\n", sum);
    return;
}


void last_bill() {
    system("cls");
    int table_num;              // 테이블 번호
    int sum = 0;                // 총가격
    int event_pizza_p = 0;      // 프리미엄 피자 할인금액
    int pizza_p_count = 0;      // 프리미엄 피자 개수, 이벤트 개수 
    int event_pizza_c = 0;      // 일반 피자 할인금액
    int pizza_c_count = 0;      // 일반 피자 개수, 이벤트 개수
    int first_order = 0;        // 첫 주문 할인 금액
    int five_order = 0;         // 5번 주문 할인 금액
    int event = 0;              // 총 할인금액
    int pay;

    order* tmp = NULL;
    order* tmp2;
    user_info* user_info = NULL;

    // 중간 영수증 테이블 선택
    printf("앉은 테이블을 입력하세요. ");
    scanf_s("%d", &table_num);

    switch (table_num) {
    case 1:
        if (t.table1 == false) {
            empty_table();
            return 0;
        }
        tmp = t.next1->next;
        user_info = t.next1;
        break;
    case 2:
        if (t.table2 == 0) {
            empty_table();
            return 0;
        }
        tmp = t.next2->next;
        user_info = t.next2;
        break;
    case 3:
        if (t.table3 == 0) {
            empty_table();
            return 0;
        }
        tmp = t.next3->next;
        user_info = t.next3;
        break;
    case 4:
        if (t.table4 == 0) {
            empty_table();
            return 0;
        }
        tmp = t.next4->next;
        user_info = t.next4;
        break;
    default:
        invalid_table();
        return;
        break;
    }

    // 주문내용(영수증)
    printf("\n\n\t\t영수증 출력\n");
    printf("---------------------------------------------------\n");
    if (tmp == NULL) {
        printf("아직 주문한 메뉴가 없습니다.\n");
        printf("---------------------------------------------------\n\n");
        return;
    }
    while (tmp != NULL) {
        printf("%20s\t%d\t%d원\n", tmp->menu, tmp->count, tmp->price);
        sum += tmp->price;
        if (tmp->pizza == 0)
            pizza_c_count = tmp->count;
        else if (tmp->pizza == 1)
            pizza_p_count = tmp->count;
        tmp = tmp->next;
    }

    // 할인 이벤트(영수증)
    printf("---------------------------------------------------\n");
    if (user_info->visit == 1) {
        first_order = 3000;
        printf("첫 방문 할인 이벤트\t\t%d원\n", first_order);
    }
    if (user_info->visit == 5) {
        five_order = 5000;
        printf("5번 방문 할인 이벤트\t\t%d원\n", five_order);
    }

    // 일반피자 할인 이벤트
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // 이벤트 개수
        event_pizza_c = (pizza_c_count * 2000);
        printf("일반피자 2판 주문 할인 이벤트  \t%d\t%d원\n", pizza_c_count, event_pizza_c);
    }

    // 프리미엄 피자 할인 이벤트
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // 이벤트 개수
        event_pizza_p = (pizza_p_count * 3000);
        printf("프리미엄피자 2판 주문 할인 이벤트\t%d\t%d원\n", pizza_p_count, event_pizza_p);
    }

    // 총가격(영수증)
    printf("---------------------------------------------------\n");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("결제금액\t\t\t\t%d원\n\n\n", sum);

    printf("총금액은  %d원 입니다.\n", sum);
    printf("결제 금액을 입력해주세요 : ");
    scanf_s("%d", &pay);
    if (sum == pay) {
        printf("결제가 완료되었습니다.\n\n");
        // 테이블 연결 끊기
        switch (table_num) {
        case 1:
            t.table1 = false;
            break;
        case 2:
            t.table2 = false;
            break;
        case 3:
            t.table2 = false;

            break;
        case 4:
            t.table2 = false;
            break;
        }
        free(user_info);
        while (tmp != NULL) {
            tmp2 = tmp->next;
            free(tmp);
            tmp = tmp2;
        }
        return;
    }
    else if (sum > pay) {
        system("cls");
        printf("결제금액이 부족합니다. 다시 결제해주세요\n\n");
        return 0;
    }
    else {
        system("cls");
        printf("총금액을 초과하였습니다. 다시 결제해주세요\n\n");
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


void menu_info() {
    system("cls");
    printf("\n\t\t          [메뉴판]           \n");
    printf("\t\t        프리미엄 피자        \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t쉬림프피자          26,000  \n");
    printf("\t\t해물피자            28,000  \n");
    printf("\t\t핫스파이시피자      24,000  \n");
    printf("\t\t슈퍼콤비네이션피자  26,000  \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t          일반 피자          \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t불고기피자          20,000  \n");
    printf("\t\t고구마피자          19,000  \n");
    printf("\t\t포테이토피자        19,000  \n");
    printf("\t\t페퍼로니피자        19,000  \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t           사이드            \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t윙&봉         (6조각) 6,000  \n");
    printf("\t\t치킨텐더      (6조각) 6,000  \n");
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
