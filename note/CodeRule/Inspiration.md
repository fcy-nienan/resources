jdk中栈的pop操作的代码
        E       obj;
        int     len = size();
        obj = peek();
        removeElementAt(len - 1);
        return obj;
我们把他展开
    
    拿一个数据,先判断容器内有没有数据,处理两种状态len==0或者len!=0
    public synchronized E peek() {
        int     len = size();

        if (len == 0)
            throw new EmptyStackException();
        return elementAt(len - 1);
    }
    访问一个元素,先看访问下表是否越界,处理两种状态
    public synchronized E elementAt(int index) {
        if (index >= elementCount) {
            throw new ArrayIndexOutOfBoundsException(index + " >= " + elementCount);
        }

        return elementData(index);
    }
    这个就是通过index获取一个元素,并且规定index必须是有效的
    E elementData(int index) {
        return (E) elementData[index];
    }
    移除一个元素
    判断index的有效性
    public synchronized void removeElementAt(int index) {
        modCount++;
        if (index >= elementCount) {
            throw new ArrayIndexOutOfBoundsException(index + " >= " +
                                                     elementCount);
        }
        else if (index < 0) {
            throw new ArrayIndexOutOfBoundsException(index);
        }
        int j = elementCount - index - 1;
        if (j > 0) {
            System.arraycopy(elementData, index + 1, elementData, index, j);
        }
        elementCount--;
        elementData[elementCount] = null; /* to let gc do its work */
    }
    显然，里面的每个if-else判断都需要执行，但这样会不会稍显累赘？
    肯定会，但这是为了可维护性和追求代码质量，并不在意这几个if-else造成的些许性能