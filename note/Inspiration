jdk中栈的pop操作的代码
        E       obj;
        int     len = size();
        obj = peek();
        removeElementAt(len - 1);
        return obj;
我们把他展开
    public synchronized E peek() {
        int     len = size();

        if (len == 0)
            throw new EmptyStackException();
        return elementAt(len - 1);
    }
    public synchronized E elementAt(int index) {
        if (index >= elementCount) {
            throw new ArrayIndexOutOfBoundsException(index + " >= " + elementCount);
        }

        return elementData(index);
    }
    E elementData(int index) {
        return (E) elementData[index];
    }
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