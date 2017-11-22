'''
实验目的：模拟请求分页存储管理算法，了解页表、地址变换、缺页中断、页面转换算法
问题描述：
设有200条指令依次存储在1-200号的外存连续空间中。系统在内存中为进程分配的物理块数为3，指令的物理块号从100开始。页面大小分别为4、8。
实验要求：
1输入1-200间的数字（代表指令号）分别显示不同页面大小下的相关结果（见2-4条），输入“Q”则结束程序，输入其他内容则提示错误
2输入数字后显示当前指令对应的页面号、页内偏移量及物理块号
3显示当前内存中的页面号（初始状态为0、0、0）、是否产生缺页中断及是否需要页面置换
4若需置换页面，请显示换出页面及换入页面的页面号（页面转换算法选用LRU算法）
'''

#页表设定
#页面大小
Page_lenth=4
#Page_lenth=8


#指令起始位置
Code_segment_start_address = 100

#内存可分配物理块
Program_enable_block = 3

#程序
program = []
#内存
memory = []

#计数器初始化
all_right_input = 0
success = 0
need_exchange = 0



def create_memory():
    #设定内存

    for i in range(Code_segment_start_address,Code_segment_start_address + 3):
        memory.append([i-Code_segment_start_address,i,0,0])#偏址，物理地址，加载程序页，上一次使用
        #初始状态要求0
    
def create_program():
    #构造程序
    for i in range(200):
        program.append([i,'CC'])#地址，内容

def create_page_list():
    #分页并创建页表
    page_list=[]
    j=1
    for i in program:
        #页表ID，页表首地址
        if i[0] % 4 == 0:
            page_list.append([j,i[0]])
            j = j+1
    #print(page_list)


def get_input():
    #获取用户输入
    while 1:
        uin = input("请输入需要调用的指令所在位置")
        #若输入Q或q则退出
        if uin == 'Q' or uin == 'q':
            input("收到退出指令，按任意键结束")
            exit(0)
        else:
            if uin == 'T' or uin == 't':
                show_exchange_info()
            else:
                try:
                    input_address = int(uin)
                    if input_address > 200:
                        print("超出允许范围（0~200）")
                    else:
                        return input_address
                except:
                    print("输入非法，请重试")

def show_exchange_info():
    try:
        success_rate = success / all_right_input
        exchange_rate = 1 - success_rate
        print("共有 ",all_right_input," 次有效输入\n不续置换成功访问 ",success," 次\n成功率： ",success_rate*100," % ，置换率： ",exchange_rate*100," %")
    except:
        print("显示发生了错误，可能在计算过程中出现了除数为0的情况，请尝试继续运行程序后再次显示")
        

def get_page_location(i_address):
    #定位页
    get_page = int(i_address / 4)
    return get_page+1

def show_page_info(page):
    #显示页详情
    gs = "{:^9}\t{:^8}\t{:^8}"#输出格式
    out_info = []#输出列表
    out_info.append(['偏址','物理地址','内容'])#输出title
    k = 0
    for i in range(page*4-4,page*4):
        j = get_program(i)
        out_info.append([k,j[0],j[1]])
        k = k+1
    for i in out_info:
        print(gs.format(i[0],i[1],i[2]))

def get_program(a):
    #获取“内存”值
    return program[a]

def show_memory_info():
    #显示内存信息
    print("\n\n当前本程序占用内存情况")
    gs = "{:^9}\t{:^8}\t{:^8}\t{:^8}"#输出格式
    out_info = []#输出列表
    out_info.append(['编号','内存地址','程序页','距离上次访问'])#输出title
    k = 0
    for i in range(Program_enable_block):
        out_info.append([memory[i][0],memory[i][1],memory[i][2],memory[i][3]])
        k = k+1
    for i in out_info:
        print(gs.format(i[0],i[1],i[2],i[3]))
        
def memory_use_time_update(i):
    #更新内存最近使用时间
    for j in range(Program_enable_block):
        if i == j:
            memory[j][3] = 0;
        else:
            memory[j][3] = memory[j][3] + 1;

def get_smallist_memory():
    s = -1;
    for i in range(Program_enable_block):
        if memory[i][3] > s:
            s = memory[i][3]
            p = i
        else:
            continue
    return p
    

def exchange_memory(target):
    #交换内存
    exchange_from = get_smallist_memory()
    old = memory[exchange_from][2]
    memory[exchange_from][2] = target
    memory[exchange_from][3] = 0
    re = [exchange_from,old]
    return re;


def main():
    #初始化
    create_program()
    create_memory()
    create_page_list()
    input("使用说明：\n\t1.根据提示输入需要调用的指令地址\n\t2.本实验中所有指令设定均为CC（DOS中断）\n\t3.输入Q（或q）来结束程序\n\t4.输入T(t)可查看置换情况\n\n按回车来开始程序")


    #主程序
    while 1:
        #此处无限循环，判断输入子程序里有处理程序退出
        address_input = get_input()
        global all_right_input
        global success
        global need_exchange
        page = get_page_location(address_input)
        all_right_input = all_right_input + 1
        print("\n地址：",address_input,"\n页：",page,"偏：",address_input%4,"\n")
        show_page_info(get_page_location(address_input))
        show_memory_info()
        need_exchange = 1;
        print("请求的页为 " , page , "内存中的页有" ,memory[0][2],",",memory[1][2],",",memory[2][2]," 页")
        for i in range(Program_enable_block):
            if page == memory[i][2]:
                print("不需要进行页的置换")
                need_exchange = 0;#不需要置换
                success += 1
                break;
            
        if need_exchange:
            print("需要进行页置换")
            need_exchange += 1
            re = exchange_memory(page)
            memory_use_time_update(re[0])
            if re[1] == 0:
                print("页 ",page," 被换入未分配使用的内存\n\n被置换后的内存情况为：")
            else:
                print("\n内存块",re[0],"（原 ",re[1]," 页）被换出内存，页 ",page," 被换入内存\n\n被置换后的内存情况为：")
        else:
            memory_use_time_update(i)
            print("\n内存距上次使用时间被更新\n\n更新后的结果为：")
               
        show_memory_info()


    
main()
input("按任意键退出")
