LL  value>node&&leftH-rightH<-1
1
    2
        3
Node n=root.right
root.right=n.left;
n.left=root;
return n;
RR  value<node&&leftH-rightH>1
        1
    2   
3
Node n=root.left;
root.left=n.right;
n.right=root;
return n;
LR  value<node&&leftH-rightH>1
    1
2
    3

RL  value>node&&rightH-leftH>1
    1
        2
    3
