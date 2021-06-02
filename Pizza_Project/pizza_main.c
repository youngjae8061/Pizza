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
void new_customer();            // �մ� ����
void middle_bill();		        // �߰� ��� ������
void last_bill();	            // ���� ������


char Premium[4][20] = { "����������", "�ع�����", "�ֽ����̽�����", "�����޺���̼�����" };
char Classic[4][20] = { "�Ұ������", "��������",  "������������",  "����δ�����" };
/*char price[14][3][20] = { 
    {"�Ұ������", "20000", "0"}, {"��������", "19000", "0"}, {"������������", "19000", "0"}, {"����δ����� ", "19000", "0"}, 
    {"����������", "26000", "1"}, {"�ع�����", "28000", "1"}, {"�ֽ����̽�����", "24000", "1"}, {"�����޺���̼�����", "26000", "1"},
    {"��&��", "6000", "2"}, {"ġŲ�ٴ�", "6000", "2"}, {"���İ�Ƽ", "7000", "2"}, {"ġ�", "5000", "2"},
    {"�ݶ�", "2000", "2"}, {"���̴�", "2000", "2"} 
};*/



int main() {
	SetConsoleTitle(TEXT("Pizza Store - ����������Ʈ 13�й� 8��")); // �ܼ�â ����
    
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
                    for (; tmp->next != NULL;)
                    {
                        tmp = tmp->next;
                    }
                    input_menu(tmp);
                    print_menu(order_h);
                    break;
                case 2: // �ֹ� ����
                    printf("~ \n");
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


void input_menu(order* start)
{
    system("cls");
    order* current = NULL;

    current = (order*)malloc(sizeof(order));
    start->next = current;
    current->next = NULL;

    menu_info();

    //order memu, count, price 
    printf("\n\n0.�����̾� ���� 1.�Ϲ� ���� 2.���̵� 3.����\n----------------------------------------------\n�޴� ������ �Է����ּ���. : ");
    scanf_s("%d", &current->pizza);
    getchar();
    printf("\n\n�ֹ��Ͻ� �޴��� �����ּ���. : ");
    //scanf_s("%s", current->name);
    gets_s(current->menu, 20);
    printf("������ �Է����ּ���. : ");
    scanf_s("%d", &current->count);
    printf("������ �Է��Ͻÿ� : ");
    scanf_s("%d", &current->price);
    printf("");
    // �����̾� ���� 2�Ǹ��� 3000 ����, �Ϲ� ���� 2�Ǹ��� 2000 ����
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
    printf("\n\n�ֹ��� �� ���\n");
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


void menu_info()
{
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