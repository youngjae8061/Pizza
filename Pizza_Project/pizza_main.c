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


// ����� ���� ���
typedef struct user_info {
    char name[20];		// ����� �̸�
    int phone;			// ����� ��ȭ��ȣ
    int visit;			// ����� �湮 Ƚ��
    struct order* next;	//
}user_info;
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
tb t = { false, NULL, false, NULL, false, NULL, false, NULL };


void program_info();            // ���α׷� ���� ���
void user_menu();               // ����� �޴� ���
void menu_info();               // ���� �޴� ���
void input_menu();              // �޴� �Է�(�����)
void modify_menu();             // �ֹ��� �޴� ����
void modify_bot(order* find);  // ������ �޴� �����ϴ� �Լ�
void new_customer();            // �մ� ����
void middle_bill();		        // �߰� ��� ������
void last_bill();	            // ���� ������

char menu_price[14][3][20] = {
    {"�Ұ������", "20000", "0"}, {"��������", "19000", "0"}, {"������������", "19000", "0"}, {"���۷δ����� ", "19000", "0"},
    {"����������", "26000", "1"}, {"�ع�����", "28000", "1"}, {"�ֽ����̽�����", "24000", "1"}, {"�����޺���̼�����", "26000", "1"},
    {"��&��", "6000", "2"}, {"ġŲ�ٴ�", "6000", "2"}, {"���İ�Ƽ", "7000", "2"}, {"ġ�", "5000", "2"},
    {"�ݶ�", "2000", "2"}, {"���̴�", "2000", "2"}
};



int main() {
    SetConsoleTitle(TEXT("Pizza Store - ����������Ʈ 13�й� 8��")); // �ܼ�â ����
    system("mode con:cols=150 lines=70");

    int num = 0;
    mng_h = (mng*)malloc(sizeof(mng)); // mng_h �� �ʱ�ȭ
    strcpy(mng_h->name, "�ʱ�ȭ");
    mng_h->phone = 0;
    mng_h->visit = 0;
    mng_h->next = NULL;

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
            switch (num) {
            case 1: // �ֹ�
                system("cls");
                menu_info();
                input_menu();
                break;
            case 2: // �ֹ� ����
                system("cls");
                modify_menu();
                break;
            case 3: // �߰� ��꼭 ���
                system("cls");
                middle_bill();
                break;
            case 4: // ���
                system("cls");
                last_bill();
                break;
            case 5: // �մ�����
                system("cls");
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
    int t_num = 0;    // ���̺� ��ȣ ����
    int select = 0;   // �޴� ����

    order* find;

    printf("��� ���̺� �Դϱ�?");
    scanf_s("%d", &t_num);
    switch (t_num) {
    case 1:
        if (t.table1 == false) {
            printf("�Է��Ͻ� �ڸ��� ����ִ� ���̺��Դϴ�. �ٽ� Ȯ�����ּ���.\n");
            return 0;
        }
        find = t.next1->next;
        modify_bot(find);
        break;
    case 2:
        if (t.table2 == false) {
            printf("�Է��Ͻ� �ڸ��� ����ִ� ���̺��Դϴ�. �ٽ� Ȯ�����ּ���.\n");
            return 0;
        }
        find = t.next2->next;
        modify_bot(find);
        break;
    case 3:
        if (t.table3 == false) {
            printf("�Է��Ͻ� �ڸ��� ����ִ� ���̺��Դϴ�. �ٽ� Ȯ�����ּ���.\n");
            return 0;
        }
        find = t.next3->next;
        modify_bot(find);
        break;
    case 4:
        if (t.table4 == false) {
            printf("�Է��Ͻ� �ڸ��� ����ִ� ���̺��Դϴ�. �ٽ� Ȯ�����ּ���.\n");
            return 0;
        }
        find = t.next4->next;
        modify_bot(find);
        break;
    default:
        system("cls");
        printf("\n���� ���� ���̺��� 1, 2, 3, 4�� ���̺�� �� 4�� �Դϴ�. ���̺� ��ȣ�� Ȯ���� �ּ���\n");
        break;
    }
}


void modify_bot(order* find) {
    int temp_count = 0; // ���� ���� �ӽ� ����(0���� ����)
    char modify[20];        // ������ �޴��� �̸�
    int select;
    order* head;    // ��� ���
    order* temp;    // ���� ���� �� ��� �����ϱ� ���� ���

    head = find;
    temp = NULL;

    while (1) {
        printf("�޴��� �������ּ���\n");
        printf("1. �޴� �����ϱ�\n");
        printf("(1�� ������ ����). �ʱ�ȭ������ ���ư���\n");
        scanf_s("%d", &select);
        if (select == 1) {
            printf("�޴����� �Է����ּ��� : ");
            scanf_s("%s", modify, sizeof(modify));
            while (1) { // �ش� �޴� ã�� ����
                // �����ϱ� ���� �Է� ���� modify�� find�� menu�� ���� ���
                if (!(strcmp(modify, find->menu) == 0) && find->next == NULL) {
                    printf(" �׷� �޴��� �����ϴ�!!\n\n");
                    return 0;
                }
                // �����ϱ� ���� �Է� ���� modify�� find�� menu�� ���� ������ ���
                if (strcmp(modify, find->menu) == 0) {
                    printf("������ �������ּ��� : ");
                    scanf_s("%d", &temp_count);
                    if (temp_count == 0) { // ������ 0�϶� �ش� ��� ���� + �յ� ��� �̾��ֱ�
                        while (1) { // ������ 0���� ����Ǿ� �ش� ��� free() + �յ� ��� �̾��ֱ�
                                // modify�� head�� menu�� ������� ��, �Ǿ��� ��带 ������ ���
                            if (strcmp(modify, head->menu) == 0) {
                                head = find->next;
                            }
                            // find�� ���� ��尡 NULL�� ��� ��, �� ������ ��带 ������ ���
                            else if (find->next == NULL) {
                                temp->next = NULL;
                            }
                            // �� ���� ���
                            else {
                                temp->next = find->next;
                            }
                            free(find);
                            break;
                            // �ش� ���ڸ� ã������ ���� ���� �̵�
                            temp = find;
                            find = find->next;
                        }
                        printf("���� �߽��ϴ�!!!\n\n");
                        break;
                    }
                    // 0���� �ٸ� �������� ����ɶ� 
                    find->count = temp_count;
                    for (int i = 0; i < 14; i++) {
                        if (strcmp(find->menu, menu_price[i][0]) == 0)
                            find->price = atoi(menu_price[i][1]) * temp_count;
                    }
                    system("cls");
                    printf("���� �����߾��!\n");  // ���� ���� ����
                    break;
                }
                find = find->next; // �ش� �޴� ���� �� ���� ���� �̵�
            }
        }
        else { // ����ȭ������ ���ư���(2)�� ������ ��
            return 0;
        }
    }
}


void input_menu() {
    int table_number; // ���� ���̺� ��ȣ
    char menu[20]; //�޴�
    int count; //�޴��� ����
    int select;
    bool input = false;
    order* tmp = NULL; //�ֹ� ����� ���(���̺� -> �������� -> tmp)
    order* pre = NULL; //�ֹ� ����� �������� ����Ű�� ������
    user_info* user_info = NULL;

    printf("���� ���̺��� �Է��ϼ���.\n");
    scanf_s("%d", &table_number, sizeof(table_number));

    switch (table_number) {
    case 1:
        if (t.table1 == false) {
            printf("�ش� ���̺��� ����ֽ��ϴ�.");
            return;
        }
        tmp = t.next1->next; //�ֹ� ����� ���(���̺� -> �������� -> tmp)
        user_info = t.next1;
        break;
    case 2:
        if (t.table2 == false) {
            printf("�ش� ���̺��� ����ֽ��ϴ�.");
            return;
        }
        tmp = t.next2->next; //�ֹ� ����� ���(���̺� -> �������� -> tmp)
        user_info = t.next2;
        break;
    case 3:
        if (t.table3 == false) {
            printf("�ش� ���̺��� ����ֽ��ϴ�.");
            return;
        }
        tmp = t.next3->next; //�ֹ� ����� ���(���̺� -> �������� -> tmp)
        user_info = t.next3;
        break;
    case 4:
        if (t.table4 == false) {
            printf("�ش� ���̺��� ����ֽ��ϴ�.");
            return;
        }
        tmp = t.next4->next; //�ֹ� ����� ���(���̺� -> �������� -> tmp)
        user_info = t.next4;
        break;
    default:
        system("cls");
        printf("\n���� ���� ���̺��� 1, 2, 3, 4�� ���̺�� �� 4�� �Դϴ�. ���̺� ��ȣ�� Ȯ���� �ּ���\n");
        break;
    }

    while (1) {
        system("cls");
        printf("�޴��� �������ּ���\n");
        printf("1. �ֹ��ϱ�\n");
        printf("(1�� ������ ����). �ʱ�ȭ������ ���ư���\n");
        scanf_s("%d", &select);
        if (select == 1) {
            printf("�ֹ��Ͻ� �޴��� �����ּ���. \n");
            scanf_s("%s", menu, sizeof(menu));

            for (int i = 0; i < 14; i++) {
                if (strcmp(menu_price[i][0], menu) == 0) { //�޴��ǿ� �ִ� �޴��� ����
                    printf("������ �Է����ּ���. : ");
                    scanf_s("%d", &count, sizeof(count));

                    if (tmp == NULL) { // ù �ֹ�
                        tmp = (order*)malloc(sizeof(order));
                        strcpy(tmp->menu, menu);
                        tmp->count = count;
                        tmp->price = atoi(menu_price[i][1]) * count;
                        tmp->pizza = atoi(menu_price[i][2]);
                        tmp->next = NULL;
                        user_info->next = tmp;
                        break;
                    }

                    while (tmp != NULL) { // ù �ֹ��� �ƴϸ� ���� �޴��� �ֹ� �ߴ��� ã��
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
                    tmp = (order*)malloc(sizeof(order)); //���� �޴��� ���ٸ� ��� �������� �߰�
                    pre->next = tmp;
                    strcpy(tmp->menu, menu);
                    tmp->count = count;
                    tmp->price = atoi(menu_price[i][1]) * count;
                    tmp->pizza = atoi(menu_price[i][2]);
                    tmp->next = NULL;
                }
                if (i == 13)
                    printf("�޴��ǿ� ���� �޴��Դϴ�.\n �ٽ� �ֹ����ּ���.\n");
            }
        }
        else
            return;
    }
}

void new_customer() {
    int table_count = 0; //���� ���̺� ��
    int table_number; //���̺� ��ȣ
    char name[20]; //������� �̸�
    int phone; //������� ��ȭ��ȣ ���ڸ�
    int visit; //������� �湮 Ƚ��
    mng* tmp = mng_h; //�湮 Ƚ���� �������� ���� ��ȸ ������
    mng* pre = mng_h; //������ ��带 ����Ű�� ������
    mng* new_user = NULL; //���ο� ������� ������ �߰��ϱ� ���� ������
    user_info* ui;
    printf("���� ���� ���̺��� "); //���� ���̺� ��ȣ�� �˷��ְ� �ڸ��� ������ ����
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

    switch (table_number) {
    case 1:
        t.table1 = true; //���� ���̺� �ڸ� �������� ����
        user_info1 = (user_info*)malloc(sizeof(user_info)); //���̺� ���� ����� ���� �Է�
        ui = user_info1;
        t.next1 = ui;
        break;
    case 2:
        t.table2 = true; //���� ���̺� �ڸ� �������� ����
        user_info2 = (user_info*)malloc(sizeof(user_info)); //���̺� ���� ����� ���� �Է�
        ui = user_info2;
        t.next2 = ui;
        break;
    case 3:
        t.table3 = true; //���� ���̺� �ڸ� �������� ����
        user_info3 = (user_info*)malloc(sizeof(user_info)); //���̺� ���� ����� ���� �Է�
        ui = user_info3;
        t.next3 = ui;
    case 4:
        t.table4 = true; //���� ���̺� �ڸ� �������� ����
        user_info4 = (user_info*)malloc(sizeof(user_info)); //���̺� ���� ����� ���� �Է�
        ui = user_info4;
        t.next4 = ui;
        break;
    default:
        system("cls");
        printf("\n���� ���� ���̺��� 1, 2, 3, 4�� ���̺�� �� 4�� �Դϴ�. ���̺� ��ȣ�� Ȯ���� �ּ���\n");
        return;
        break;
    }

    printf("�̸��� �Է��ϼ���.\n");
    scanf_s("%s", name, sizeof(name));
    printf("��ȭ��ȣ ���ڸ��� �Է��ϼ���.\n");
    scanf_s("%d", &phone, sizeof(phone));
    strcpy(ui->name, name);

    ui->phone = phone;
    ui->visit = 1;
    ui->next = NULL;

    while (tmp != NULL) { //�湮 Ƚ�� ��������
        if (strcmp(tmp->name, name) == 0) {
            if (tmp->phone == phone) {
                tmp->visit++;
                visit = tmp->visit;
                return;
            }
        }
        pre = tmp;
        tmp = tmp->next;
    }

    new_user = (mng*)malloc(sizeof(mng));//���ο� ����ڸ� user_manage�� ���� �Է�
    strcpy(new_user->name, name);
    new_user->phone = phone;
    new_user->visit = 1;
    new_user->next = NULL;
    pre->next = new_user; //user_manage�� ������ ��� �ڿ� �߰�

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

    order* tmp = NULL;
    user_info* user_info = NULL;

    // �߰� ������ ���̺� ����
    printf("����Ͻ� ���̺� ��ȣ�� �Է����ּ��� : ");
    scanf_s("%d", &table_num, sizeof(table_num));

    switch (table_num) {
    case 1:
        if (t.table1 == false) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = t.next1->next;
        user_info = t.next1;
        break;
    case 2:
        if (t.table2 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = t.next2->next;
        user_info = t.next2;
        break;
    case 3:
        if (t.table3 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = t.next3->next;
        user_info = t.next3;
        break;
    case 4:
        if (t.table4 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = t.next4->next;
        user_info = t.next4;
        break;
    default:
        system("cls");
        printf("\n���� ���� ���̺��� 1, 2, 3, 4�� ���̺�� �� 4�� �Դϴ�. ���̺� ��ȣ�� Ȯ���� �ּ���\n");
        return;
        break;
    }

    // �ֹ�����(������)
    printf("\n\n\t\t�߰� ������ ���\n");
    printf("---------------------------------------------------\n");
    if (tmp == NULL) {
        printf("���� �ֹ��� �޴��� �����ϴ�.\n");
        return;
    }
    while (tmp != NULL) {
        printf("%20s\t%d\t%d��\n", tmp->menu, tmp->count, tmp->price);
        sum += tmp->price;
        if (tmp->pizza == 0)
            pizza_c_count = tmp->count;
        else if (tmp->pizza == 1)
            pizza_p_count = tmp->count;
        tmp = tmp->next;
    }

    // ���� �̺�Ʈ(������)
    printf("---------------------------------------------------\n");
    if (user_info->visit == 1) {
        first_order = 3000;
        printf("ù �湮 ���� �̺�Ʈ\t\t%d\n", first_order);
    }
    if (user_info->visit == 5) {
        five_order = 5000;
        printf("5�� �湮 ���� �̺�Ʈ\t\t%d��\n", five_order);
    }

    // �Ϲ����� ���� �̺�Ʈ
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // �̺�Ʈ ����
        event_pizza_c = (pizza_c_count * 2000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ  \t%d\t%d��\n", pizza_c_count, event_pizza_c);
    }

    // �����̾� ���� ���� �̺�Ʈ
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // �̺�Ʈ ����
        event_pizza_p = (pizza_p_count * 3000);
        printf("�����̾����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d��\n", pizza_p_count, event_pizza_p);
    }

    // �Ѱ���(������)
    printf("---------------------------------------------------\n");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("�����ݾ�\t\t\t\t%d��\n\n\n", sum);
    return;
}


void last_bill() {
    int table_num;              // ���̺� ��ȣ
    int sum = 0;                // �Ѱ���
    int event_pizza_p = 0;      // �����̾� ���� ���αݾ�
    int pizza_p_count = 0;      // �����̾� ���� ����, �̺�Ʈ ���� 
    int event_pizza_c = 0;      // �Ϲ� ���� ���αݾ�
    int pizza_c_count = 0;      // �Ϲ� ���� ����, �̺�Ʈ ����
    int first_order = 0;        // ù �ֹ� ���� �ݾ�
    int five_order = 0;         // 5�� �ֹ� ���� �ݾ�
    int event = 0;              // �� ���αݾ�
    int pay;

    order* tmp = NULL;
    order* tmp2;
    user_info* user_info = NULL;

    // �߰� ������ ���̺� ����
    printf("����Ͻ� ���̺� ��ȣ�� �Է����ּ��� : ");
    scanf_s("%d", &table_num);

    switch (table_num) {
    case 1:
        if (t.table1 == false) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = t.next1->next;
        user_info = t.next1;
        break;
    case 2:
        if (t.table2 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = t.next2->next;
        user_info = t.next2;
        break;
    case 3:
        if (t.table3 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = t.next3->next;
        user_info = t.next3;
        break;
    case 4:
        if (t.table4 == 0) {
            printf("���� �ڸ��� ����ִ� ���̺��Դϴ�.\n");
            return 0;
        }
        tmp = t.next4->next;
        user_info = t.next4;
        break;
    default:
        system("cls");
        printf("\n���� ���� ���̺��� 1, 2, 3, 4�� ���̺�� �� 4�� �Դϴ�. ���̺� ��ȣ�� Ȯ���� �ּ���\n");
        return;
        break;
    }

    // �ֹ�����(������)
    printf("\n\n\t\t������ ���\n");
    printf("---------------------------------------------------\n");
    if (tmp == NULL) {
        printf("���� �ֹ��� �޴��� �����ϴ�.\n");
        return;
    }
    while (tmp != NULL) {
        printf("%20s\t%d\t%d��\n", tmp->menu, tmp->count, tmp->price);
        sum += tmp->price;
        if (tmp->pizza == 0)
            pizza_c_count = tmp->count;
        else if (tmp->pizza == 1)
            pizza_p_count = tmp->count;
        tmp = tmp->next;
    }

    // ���� �̺�Ʈ(������)
    printf("---------------------------------------------------\n");
    if (user_info->visit == 1) {
        first_order = 3000;
        printf("ù �湮 ���� �̺�Ʈ\t\t%d��\n", first_order);
    }
    if (user_info->visit == 5) {
        five_order = 5000;
        printf("5�� �湮 ���� �̺�Ʈ\t\t%d��\n", five_order);
    }

    // �Ϲ����� ���� �̺�Ʈ
    if (pizza_c_count >= 2) {
        pizza_c_count = (pizza_c_count / 2);   // �̺�Ʈ ����
        event_pizza_c = (pizza_c_count * 2000);
        printf("�Ϲ����� 2�� �ֹ� ���� �̺�Ʈ  \t%d\t%d��\n", pizza_c_count, event_pizza_c);
    }

    // �����̾� ���� ���� �̺�Ʈ
    if (pizza_p_count >= 2) {
        pizza_p_count = (pizza_p_count / 2);   // �̺�Ʈ ����
        event_pizza_p = (pizza_p_count * 3000);
        printf("�����̾����� 2�� �ֹ� ���� �̺�Ʈ\t%d\t%d��\n", pizza_p_count, event_pizza_p);
    }

    // �Ѱ���(������)
    printf("---------------------------------------------------\n");
    event = (event_pizza_p + event_pizza_c + first_order + five_order);
    sum = sum - event;
    printf("�����ݾ�\t\t\t\t%d��\n\n\n", sum);

    printf("�ѱݾ���  %d�� �Դϴ�.\n", sum);
    printf("���� �ݾ��� �Է����ּ��� : ");
    scanf_s("%d", &pay);
    if (sum == pay) {
        printf("������ �Ϸ�Ǿ����ϴ�.\n");
        // ���̺� ���� ����
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


void menu_info() {
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
