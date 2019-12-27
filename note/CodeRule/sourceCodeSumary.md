除了一些基础的bean类，在所有类中都添加一个static的日志对象

 if (RpcProgramNfs3.LOG.isDebugEnabled()) {
      RpcProgramNfs3.LOG.debug(WRITE_RPC_END + xid);
    }
日志级别的控制还真是通过这种if,else控制的



命令行的解析
    if (opt.equals("-server")) { // - 开头的为参数
                            options.put("server", it.next()); // 参数后一个内容是参数值
                        } else if (opt.equals("-timeout")) {
                            options.put("timeout", it.next());
                        } else if (opt.equals("-r")) {
                            options.put("readonly", "true");
                        }
