with open("in", "r") as f:
    s = f.read();
    l = s.split(",")
    count = 0;
    for a in l:
        print "ans[%d] = %s;" % (count, a.split()[0]) 
        count = count + 1
