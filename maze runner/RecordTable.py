import sys
from easygui import msgbox,enterbox,ynbox




def read_record():
    records = open('records.txt')
    for line in records:
        print (line,"\n")
    records.close()





def new_record(score):
    text1 = "Game is over. Your score is " + str(score) + ". Enter your name for records table : "
    name = ["Anonim228"]
    not_repeated_name = True

    f = open('records.txt', 'a')
    msg = text1
    title = "New record"
    button = "Enter my name!"

    msgbox(msg, title, button)
    fieldValues2 = enterbox(msg, title)
    if fieldValues2 != None:
        name=[fieldValues2]
        f.write('\n'+fieldValues2 + ' ' + str(score))
    f.close()

    records = open('records.txt')
    count = int(0)
    rec_name = []
    rec_num = []
    for line in records:
        rec_name.append(line.split()[0])
        rec_num.append(int(line.split()[1]))
        S = ""
        if S.join(name) == rec_name[count] and name !=["Anonim228"]:
            rec_num[count] = score
            not_repeated_name = False
        count += 1
    records.close()
    if not_repeated_name:
        records = open('records.txt','w')
        table_manage = False
        rec_count = 0
        for i in range(count):
            if rec_num[i] > score or table_manage and rec_count < 15:
                rec_count +=1
                records.write(rec_name[i] + " " + str(rec_num[i]) + '\n')
            else:
                if rec_count < 14:
                    S = ""
                    name = S.join(name)
                    records.write(name + " " + str(score) + '\n')
                    records.write(rec_name[i] + " " + str(rec_num[i]) + '\n')
                    table_manage = True
                else:
                    if rec_count < 15:
                        S = ""
                        name = S.join(name)
                        records.write(name + " " + str(score) + '\n')
                        table_manage = True

        records.close()
        HoG()

def HoG():
    msg = "Do you want to visit our Hall of Glory?"
    title = "HoG"
    choices = ("[<F1>]OK", "[<F2>]Cancel")
    if ynbox(msg, title, choices, image=None, default_choice=choices[0], cancel_choice=choices[1]):
        f = open('records.txt')
        k = 0
        s = ''
        for line in f:
            s = s + line + '\n'
            k += 1
            if k == 11:
                break
        msg = s
        title = "HALL OF GLORY!!!"
        msgbox(msg, title)

        f.close()
    else:
        sys.exit()


