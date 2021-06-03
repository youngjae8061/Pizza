#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdbool.h>	    // bool, true, false�� ���ǵ� ��� ����
#include<Windows.h>		// ������ �ܼ�â ���� ��� ���� 


   /////////////////////////////////////////////////
  //              ����������Ʈ 8��                //
 // ���� - ��â��   ���� - ������, ����, �̿��� //
////////////////////////////////////////////////


// �ֹ� ���
typedef struct order {
	char menu[20];		// �޴� �̸�
	int count;			// �ش� �޴� ����
	int price;			// ����
	int pizza;			// 0�̸� �Ϲ�, 1�̸� �����̾�, 2�̸� ���̵� �� ����
	struct order* next;	//
}order;
order* order_h;			// �ֹ������ �� �� ��� (���� �ֱٿ� ������ ��尡 ��) 
order* order_end;


// ����� ���� ���
typedef struct user_info{
	char name[20];		// ����� �̸�
	int phone;			// ����� ��ȭ��ȣ
	int visit;			// ����� �湮 Ƚ��
	struct order* next;	//
}user_info;
user_info* user_info_h;		    // ����� ���� ����� �� �� ��� (���� �ֱٿ� ������ ��尡 ��) 
user_info* user_info1 = NULL, * user_info2 = NULL, * user_info3 = NULL, * user_info4 = NULL;


// �� ���� ���
typedef struct user_manage {
	char name[20];				// ����� �̸�
	int phone;					// ����� ��ȭ��ȣ
	int visit;					// ����� �湮 Ƚ��
	struct user_manage* next;	//
}mng;
mng* mng_h;					    // �� ���� ����� �� �� ��� (���� �ֱٿ� ������ ��尡 ��) 


// ���̺� ���� ���
typedef struct table {		
    bool table1;    // True �ڸ� ����, False �ڸ� ����
    struct user_info* next1;
    bool table2;
    struct user_info* next2;
    bool table3;
    struct user_info* next3;
    bool table4;
    struct user_info* next4;
}tb;
tb* tb_h;                       // ���̺� ����� �� �� ��� (���� �ֱٿ� ������ ��尡 ��) 
tb t = { false, NULL, false, NULL, false, NULL, false, NULL };


void program_info();            // ���α׷� ���� ���
void user_menu();               // ����� �޴� ���
void menu_info();               // ���� �޴� ���
void input_menu(order* start);  // �޴� �Է�(�����)
void print_menu(order* start);  // ����ڰ� �ֹ��� ���
void modify_menu();             // �ֹ��� �޴� ����
void new_customer();            // �մ� ����
void middle_bill();		        // �߰� ��� ������
void last_bill();	            // ���� ������
void table_num();               // ���̺� ��ȣ �Է�


char menu_price[14][3][20] = { 
    {"�Ұ������", "20000", "0"}, {"��������", "19000", "0"}, {"������������", "19000", "0"}, {"����δ����� ", "19000", "0"}, 
    {"����������", "26000", "1"}, {"�ع�����", "28000", "1"}, {"�ֽ����̽�����", "24000", "1"}, {"�����޺���̼�����", "26000", "1"},
    {"��&��", "6000", "2"}, {"ġŲ�ٴ�", "6000", "2"}, {"���İ�Ƽ", "7000", "2"}, {"ġ�", "5000", "2"},
    {"�ݶ�", "2000", "2"}, {"���̴�", "2000", "2"} 
};



int main() {
	SetConsoleTitle(TEXT("Pizza Store - ����������Ʈ 13�й� 8��")); // �ܼ�â ����
    system("mode con:cols=150 lines=70");
    
    int num = 0;

    order_h = (order*)malloc(sizeof(order));
    order_end = (order*)malloc(sizeof(order));
    user_info_h = (user_info*)malloc(sizeof(user_info));
    mng_h = (mng*)malloc(sizeof(mng));
    tb_h = (tb*)malloc(sizeof(tb));
    user_info_h = NULL;
    mng_h = NULL;
    tb_h = NULL;
    memset(order_h, 0, sizeof(order));

    program_info();

    while (1)
    {
        user_menu();

        // �޴� �Է½� ���ڰ� �ƴ� ���� �Է½� ���ۿ� �Էµ� ���� �ʱ�ȭ
        if (scanf_s("%d", &num) == 0) {
            system("cls");
            printf("���ڸ� �Է��ϼ̳׿�. �޴��� ��.��.��. �����ּ���.\n\n");
            rewind(stdin);
        }
        else { // ���������� �޴��� �Է����� �� switch�� ����
            order* tmp = order_h;
            switch (num) {
                case 1: // �ֹ�
                    table_num();
                    menu_info();
                    for (; tmp->next != NULL;)
                    {
                        tmp = tmp->next;
                    }
                    input_menu(tmp);
                    print_menu(order_h);
                    printf("\n\n");
                    break;
                case 2: // �ֹ� ����
                    modify_menu();
                    break;
                case 3: // �߰� ��꼭 ���
                    middle_bill();
                    break;
                case 4: // ���
                    last_bill();
                    break;
                case 5: // �մ�����
                    new_customer(); 
                    break;
                case 6: return 0; // ����
                default:
                    system("cls");
                    printf(" �޴��� �ִ� 1 ~ 5 ������ ��.��.��. ��������!!!!! \n\n");
                    break;
            }
        }
    }
	return 0;
}


void modify_menu() {
    system("cls");
    t.table1 = false;
    int t_num=0;
    order_h = NULL;
    order_end = NULL;
    order* add_temp = NULL;
    order* curr = order_h;
    user_info1 = (user_info*)malloc(sizeof(user_info));
    t.next1 = user_info1;

    user_info* user = user_info_h;       
    order* menu_list = (order*)malloc(sizeof(order)); 

    printf("�̸� : ");
    scanf_s("%s", user_info1->name, 20);
    user_info1->phone = 1234;

    printf("�ȳ��ϼ��� ��ȭ��ȣ %d�� , %s��\n", user_info1->phone, user_info1->name);
    
    user_info1->next = menu_list;

    for (int i = 0; i < 2; i++) {
        printf("���ĸ� : ");
        scanf_s("%s", menu_list->menu, 50);
        menu_list->count = 2;
        menu_list->price = 18000;
        menu_list->pizza = 0;
        printf("%s, %d %d %d\n", menu_list->menu, menu_list->count, menu_list->price, menu_list->pizza);
        if (order_h == NULL) {
            menu_list->next = NULL;
            order_h = order_end = menu_list;
        }
        else {
            menu_list->next = order_h;
            order_h = menu_list;
        }
    }    

    int i = 1;          // �޴� ���ڸ� ǥ���ϱ� ���� ����
    printf("��� ���̺� �Դϱ�?");
    scanf_s("%d", &t_num);
    switch (t_num) {
        case 1:
            printf("1�� ���̺��� �޴��� ������ �����ϴ�.\n");
            if (t.table1 == true) {
                printf("�Է��Ͻ� �ڸ��� ����ִ� ���̺��Դϴ�. �ٽ� Ȯ�����ּ���.\n");
                return 0;
            }
            add_temp = order_h;
            //print_menu(order_h);
            while (add_temp != NULL) {
                printf("\n\t%d. �޴��� : %s\n\n", i++, add_temp->menu);
                printf("\t   ���� : %d\n\n", add_temp->count);
                printf("\t   ���� : %d\n\n", add_temp->price);
                add_temp = add_temp->next;
            }
            printf("\n");
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            system("cls");
            printf("\n���� ���� ���̺��� 1, 2, 3, 4�� ���̺�� �� 4�� �Դϴ�. ���̺� ��ȣ�� Ȯ���� �ּ���\n");
            break;
    }
}


void input_menu(order* start){
    //system("cls");
    order* current = NULL;

    current = (order*)malloc(sizeof(order));
    memset(current, 0, sizeof(order));
    start->next = current;
    current->next = NULL;

    getchar();
    //order memu, count
    printf("\n\n�ֹ��Ͻ� �޴��� �����ּ���. : ");
    gets_s(current->menu, 20);
    for (int i = 0; i < 14; i++){
        if (strcmp(menu_price[i][0], current->menu) == 0){
            printf("������ �Է����ּ���. : ");
            scanf_s("%d", &current->count);

            int c = current->count; //memu count value
            current->price = atoi(menu_price[i][1]) * c;
        }
        else if (strcmp(menu_price[i][0], current->menu) == 1){
            printf("�߸� �Է��ϼ̽��ϴ�.");
            break;
        }
    }
}


void print_menu(order* start){
    system("cls");
    order* tmp = start;
    int i = 0;
    tmp = tmp->next;
    printf("\n\n�ֹ��� �� ���\n");
    printf("===========================================\n");
    for (i = 0;; i++)
    {
        printf("%d | %s  %d  %d\n", i + 1, tmp->menu, tmp->count, tmp->price);

        if (tmp->next == NULL)
            break;
        tmp = tmp->next;
    }
}


void new_customer() {
    int table_count = 0;   // ���� ���̺� ��
    int table_number;      // ���̺� ��ȣ
    char name[20];         // ������� �̸�
    int phone;             // ������� ��ȭ��ȣ ���ڸ�
    int visit;             // ������� �湮 Ƚ��
    bool visit_on = false; // user_manage���� �湮 Ƚ���� �����Դ��� Ȯ���ϴ� ����

    mng* tmp = mng_h;       // �湮 Ƚ���� �������� ���� ��ȸ ������
    mng* new_user = NULL;   // ���ο� ������� ������ �߰��ϱ� ���� ������

    t.next1 = user_info1; // �� ���̺� info ������ �ʱ�ȭ
    t.next2 = user_info2;
    t.next3 = user_info3;
    t.next4 = user_info4;

    printf("���� ���� ���̺��� "); // ���� ���̺� ��ȣ�� �˷��ְ� �ڸ��� ������ ����
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
        printf("�����ϴ�.\n�˼��մϴ�.\n������ �湮���ּ���.");
        return;
    }
    else
        printf("�Դϴ�.\n");

    printf("���Ͻô� ���̺��� �����ϼ���.\n");
    scanf_s("%d", &table_number, sizeof(table_number));
    printf("�̸��� �Է��ϼ���.\n");
    scanf_s("%s", name, sizeof(name));
    printf("��ȭ��ȣ ���ڸ��� �Է��ϼ���.\n");
    scanf_s("%d", &phone, sizeof(phone));

    switch (table_number) {
        case 1:
            t.table1 = true; //���� ���̺� �ڸ� �������� ����
            user_info1 = (user_info*)malloc(sizeof(user_info)); //���̺� ���� ����� ���� �Է�
            strcpy(user_info1->name, name);
            user_info1->phone = phone;
            user_info1->next = NULL;
            while (tmp != NULL) { //�湮 Ƚ�� ��������
                if (strcmp(tmp->name, name) == 0) {
                    if (tmp->phone == phone) {
                        tmp->visit++;
                        visit = tmp->visit;
                        visit_on = true;
                    }
                }
            }
            if (visit_on == false) { //���ο� ����ڸ� user_manage�� ���� �Է�
                new_user = (mng*)malloc(sizeof(mng));
                strcpy(new_user->name, name);
                new_user->phone = phone;
                new_user->visit = 1;
                new_user->next = NULL;
                tmp->next = new_user; //user_manage�� ������ ��� �ڿ� �߰�(���� �̺κ� ���� ����)
            }
            break;
        case 2:
            t.table2 = true; //���� ���̺� �ڸ� �������� ����
            user_info2 = (user_info*)malloc(sizeof(user_info)); //���̺� ���� ����� ���� �Է�
            strcpy(user_info2->name, name);
            user_info2->phone = phone;
            user_info2->next = NULL;
            while (tmp != NULL) { //�湮 Ƚ�� ��������
                if (strcmp(tmp->name, name) == 0) {
                    if (tmp->phone == phone) {
                        tmp->visit++;
                        visit = tmp->visit;
                        visit_on = true;
                    }
                }
            }
            if (visit_on == false) { //���ο� ����ڸ� user_manage�� ���� �Է�
                new_user = (mng*)malloc(sizeof(mng));
                strcpy(new_user->name, name);
                new_user->phone = phone;
                new_user->visit = 1;
                new_user->next = NULL;
                tmp->next = new_user; //user_manage�� ������ ��� �ڿ� �߰�
            }
            break;
        case 3:
            t.table3 = true; //���� ���̺� �ڸ� �������� ����
            user_info3 = (user_info*)malloc(sizeof(user_info)); //���̺� ���� ����� ���� �Է�
            strcpy(user_info3->name, name);
            user_info3->phone = phone;
            user_info3->next = NULL;
            while (tmp != NULL) { //�湮 Ƚ�� ��������
                if (strcmp(tmp->name, name) == 0) {
                    if (tmp->phone == phone) {
                        tmp->visit++;
                        visit = tmp->visit;
                        visit_on = true;
                    }
                }
            }
            if (visit_on == false) { //���ο� ����ڸ� user_manage�� ���� �Է�
                new_user = (mng*)malloc(sizeof(mng));
                strcpy(new_user->name, name);
                new_user->phone = phone;
                new_user->visit = 1;
                new_user->next = NULL;
                tmp->next = new_user; //user_manage�� ������ ��� �ڿ� �߰�
            }
            break;
        case 4:
            t.table4 = true; //���� ���̺� �ڸ� �������� ����
            user_info4 = (user_info*)malloc(sizeof(user_info)); //���̺� ���� ����� ���� �Է�
            strcpy(user_info4->name, name);
            user_info4->phone = phone;
            user_info4->next = NULL;
            while (tmp != NULL) { //�湮 Ƚ�� ��������
                if (strcmp(tmp->name, name) == 0) {
                    if (tmp->phone == phone) {
                        tmp->visit++;
                        visit = tmp->visit;
                        visit_on = true;
                    }
                }
            }
            if (visit_on == false) { //���ο� ����ڸ� user_manage�� ���� �Է�
                new_user = (mng*)malloc(sizeof(mng));
                strcpy(new_user->name, name);
                new_user->phone = phone;
                new_user->visit = 1;
                new_user->next = NULL;
                tmp->next = new_user; //user_manage�� ������ ��� �ڿ� �߰�
            }
            break;
    }
}


void middle_bill() {
    int table_num;              // ���̺� ��ȣ
    int sum = 0;                // �Ѱ���
    int event_pizza_p = 0;      // �����̾� ���� ���αݾ�
    int pizza_p_count = 0;      // �����̾� ���� ����, �̺�Ʈ ���� 
    int event_pizza_c = 0;      // �Ϲ� ���� ���αݾ�
    int pizza_c_count = 0;      // �Ϲ� ���� ����, �̺�Ʈ ����
    int first_order = 0;        // ù �ֹ� ���� �ݾ�
    int five_order = 0;         // 5�� �ֹ� ���� �ݾ�
    int event = 0;              // �� ���αݾ�

    user_info* tmp = user_info_h;         // user ����� ���� ����
    mng* who = mng_h;           // ����� user ����
    order* list = order_h;      // order �ֹ��޴� �о���� ����

    // �߰� ������ ���̺� ����
    printf("����Ͻ� ���̺� ��ȣ�� �Է����ּ��� : ");
    scanf_s("%d", &table_num);

    switch (table_num) {
        case 1:
            if (tb_h->table1 == 0) {
                printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
                return 0;
            }
            tmp = tb_h->next1;  // ����� ���� tmp
            list = tmp->next;   // �ֹ� �޴� 
            order_h = list;  // �ֹ� �޴�(head)
            break;
        case 2:
            if (tb_h->table2 == 0) {
                printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
                return 0;
            }
            tmp = tb_h->next2;
            list = tmp->next;
            order_h = list;
            break;
        case 3:
            if (tb_h->table3 == 0) {
                printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
                return 0;
            }
            tmp = tb_h->next3;
            list = tmp->next;
            order_h = list;
            break;
        case 4:
            if (tb_h->table4 == 0) {
                printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
                return 0;
            }
            tmp = tb_h->next4;
            list = tmp->next;
            order_h = list;
            break;
    }

    // �ֹ�����(������)
    printf("\t\t�߰� ������ ���\n");
    printf("---------------------------------------------------\n");
    while (list->next != NULL) {
        printf("%s\t\t%d\t%d��\n", list->menu, list->count, list->price);
        if (list->pizza == 0)  pizza_c_count++;       // �Ϲ����� ����
        else if (list->pizza == 1) pizza_p_count++;   // �����̾� ���� ����
        list = list->next;
    }

    // ���� �̺�Ʈ(������)
    printf("---------------------------------------------------\n");
    while (who->next != NULL) {
        if ((strcmp(tmp->name, who->name) == 0) && (tmp->phone == who->phone)) {
            // ù�ֹ� �̺�Ʈ
            if (who->visit == 1) {
                first_order = 3000;
                printf("ù �湮 ���� �̺�Ʈ\t\t%d\n", first_order);
            }
            // 5�� �湮 �̺�Ʈ
            if (who->visit == 5) {
                five_order = 5000;
                printf("5�� �湮 ���� �̺�Ʈ\t\t%d\n", five_order);
            }
            break;
        }
        who = who->next;
    }

    // �Ϲ����� ���� �̺�Ʈ
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // �̺�Ʈ ����
        event_pizza_c = (pizza_c_count * 2000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d\n", pizza_c_count, event_pizza_c);
    }

    // �����̾� ���� ���� �̺�Ʈ
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // �̺�Ʈ ����
        event_pizza_p = (pizza_p_count * 3000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d\n", pizza_p_count, event_pizza_p);
    }

    // �Ѱ���(������)
    printf("---------------------------------------------------");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("�����ݾ�\t\t\t%d\n", sum);
    return 1;
}


void last_bill() {
    int pay;
    int table_num;              // ���̺� ��ȣ
    int sum = 0;                // �Ѱ���
    int event_pizza_p = 0;      // �����̾� ���� ���αݾ�
    int pizza_p_count = 0;      // �����̾� ���� ����, �̺�Ʈ ���� 
    int event_pizza_c = 0;      // �Ϲ� ���� ���αݾ�
    int pizza_c_count = 0;      // �Ϲ� ���� ����, �̺�Ʈ ����
    int first_order = 0;        // ù �ֹ� ���� �ݾ�
    int five_order = 0;         // 5�� �ֹ� ���� �ݾ�
    int event = 0;              // �� ���αݾ�

    user_info* tmp = user_info_h;         // user ����� ���� ����
    mng* who = mng_h;           // ����� user ����
    order* list = order_h;      // order �ֹ��޴� �о���� ����
    order* pre;                 // free(�ֹ��޴�)

    // �߰� ������ ���̺� ����
    printf("����Ͻ� ���̺� ��ȣ�� �Է����ּ��� : ");
    scanf_s("%d", &table_num);
    switch (table_num) {
    case 1:
        if (tb_h->table1 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = tb_h->next1;  // ����� ���� tmp
        list = tmp->next;   // �ֹ� �޴� 
        order_h = list;  // �ֹ� �޴�(head)
        break;
    case 2:
        if (tb_h->table2 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = tb_h->next2;
        list = tmp->next;
        order_h = list;
        break;
    case 3:
        if (tb_h->table3 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = tb_h->next3;
        list = tmp->next;
        order_h = list;
        break;
    case 4:
        if (tb_h->table4 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = tb_h->next4;
        list = tmp->next;
        order_h = list;
        break;
    }

    // �ֹ�����(������)
    printf("\t\t�߰� ������ ���\n");
    printf("---------------------------------------------------\n");
    while (list->next != NULL) {
        printf("%s\t\t%d\t%d��\n", list->menu, list->count, list->price);
        if (list->pizza == 0)  pizza_c_count++;     // �Ϲ����� ����
        else if (list->pizza == 1) pizza_p_count++; // �����̾� ���� ����
        list = list->next;
    }
    // ���� �̺�Ʈ(������)
    printf("---------------------------------------------------\n");
    while (who->next != NULL) {
        if ((strcmp(tmp->name, who->name) == 0) && (tmp->phone == who->phone)) {
            // ù�ֹ� �̺�Ʈ
            if (who->visit == 1) {
                first_order = 3000;
                printf("ù �湮 ���� �̺�Ʈ\t\t%d\n", first_order);
            }
            // 5�� �湮 �̺�Ʈ
            if (who->visit == 5) {
                five_order = 5000;
                printf("5�� �湮 ���� �̺�Ʈ\t\t%d\n", five_order);
            }
            break;
        }
        who = who->next;
    }

    // �Ϲ����� ���� �̺�Ʈ
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // �̺�Ʈ ����
        event_pizza_c = (pizza_c_count * 2000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d\n", pizza_c_count, event_pizza_c);
    }

    // �����̾� ���� ���� �̺�Ʈ
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // �̺�Ʈ ����
        event_pizza_p = (pizza_p_count * 3000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d\n", pizza_p_count, event_pizza_p);
    }

    // �Ѱ���(������)
    printf("---------------------------------------------------");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("�����ݾ�\t\t\t%d\n", sum);
    return sum;

    printf("�ѱݾ���  %d�� �Դϴ�.\n", sum);
    printf("���� �ݾ��� �Է����ּ��� : ");
    scanf_s("%d", &pay);
    if (sum == pay) {
        printf("������ �Ϸ�Ǿ����ϴ�.\n");
        // ���̺� ���� ����
        list = tmp->next;
        switch (table_num) {
            case 1:
                tb_h->next1 = NULL; // ���̺� ���� ����
                tb_h->table1 = 0;   // ���̺� �ڸ� ����
                free(tmp);          // ���� free
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
        printf("�����ݾ��� �����մϴ�. �ٽ� �������ּ���\n");
        return 0;
    }
    else {
        printf("�ѱݾ��� �ʰ��Ͽ����ϴ�. �ٽ� �������ּ���\n");
        return 0;
    }
}


void user_menu() {
    printf("=============================================================\n");
    printf("\t\t\t�ݰ����ϴ� �մ� ~ :)\n"); 
    printf("���� ���� �մ��� 5�� �޴��� '�մ�����' �޴��� �������ּ���.\n");
    printf("=============================================================\n\n");
    printf("\t\t1. �ֹ�\n");
    printf("\t\t2. �ֹ� ����\n");
    printf("\t\t3. �߰� ��꼭 ���\n");
    printf("\t\t4. ���\n");
    printf("\t\t5. �մ�����\n");
    printf("\t\t6. ����\n");
    printf("\n=============================================================\n\n");
    printf("�޴��� �Է��ϼ��� : ");
}


void menu_info(){
    system("cls");
    printf("\n\t\t          [�޴���]           \n");
    printf("\t\t        �����̾� ����        \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t������ ����          26,000  \n");
    printf("\t\t�ع� ����            28,000  \n");
    printf("\t\t�ֽ����̽� ����      24,000  \n");
    printf("\t\t�����޺���̼� ����  26,000  \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t          �Ϲ� ����          \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t�Ұ�� ����          20,000  \n");
    printf("\t\t���� ����          19,000  \n");
    printf("\t\t�������� ����        19,000  \n");
    printf("\t\t���۷δ� ����        19,000  \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t           ���̵�            \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t��&��(6����)          6,000  \n");
    printf("\t\tġŲ�ٴ�(6����)       6,000  \n");
    printf("\t\t���İ�Ƽ              7,000  \n");
    printf("\t\tġ�                5,000  \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t            ����             \n");
    printf("\t\t-----------------------------\n");
    printf("\t\t�ݶ�                  2,000  \n");
    printf("\t\t���̴�                2,000  \n");
    printf("\t\t-----------------------------\n\n");
}


void program_info()
{
    printf("\n\t------------------------------------------------\n");
    printf("\t               ���� ����  ���α׷�              \n");
    printf("\t   8�� : ��â��(����), ����, ������, �̿���   \n");
    printf("\t------------------------------------------------\n\n\n");
}


void table_num(){
    int table = 0;

    printf("�����Ҷ� ������ ���̺� ��ȣ(1~4)�� �����ּ���. : ");
    scanf_s("%d", &table);

    switch (table){
        case 1:
            printf("1�� ���̺��� �����ϼ̽��ϴ�.\n");
            break;
        case 2:
            printf("2�� ���̺��� �����ϼ̽��ϴ�.\n");
            break;
        case 3:
            printf("3�� ���̺��� �����ϼ̽��ϴ�.\n");
            break;
        case 4:
            printf("4�� ���̺��� �����ϼ̽��ϴ�.\n");
            break;
        default:
            printf("�߸��Է��ϼ̽��ϴ�.\n");
            return 0;
    }
}