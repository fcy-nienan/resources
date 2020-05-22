spring的ComponentScan

+ @ComponentScan* without arguments tells Spring to scan the current package and all of its sub-packages.
+ 啥都没配置的话就是告诉spring去扫描当前包和当前所有子包
+ useDefaultFilters属性,表示是否自动检测被@Component,@Repository,@Service,@Controller注解了的类(有一个默认的IncludeFilter)

```
Indicates whether automatic detection of classes annotated with {@code @Component}{@code @Repository}, {@code @Service}, or {@code @Controller} should be enabled.
```

IncludeFilter和ExcludeFilter的配置逻辑根据下面的源码推就行了
```
@ComponentScan(basePackages = "com.fcy.ComponentScan",useDefaultFilters = false,
includeFilters = @ComponentScan.Filter(type= FilterType.CUSTOM,value = com.fcy.ComponentScan.Filter.IncludeFilter.class))
```
过滤类型有很多种
```
/**
	 * Filter candidates marked with a given annotation.
	 * @see org.springframework.core.type.filter.AnnotationTypeFilter
	 */筛选被指定注解mark了的bean
	ANNOTATION,

	/**
	 * Filter candidates assignable to a given type.
	 * @see org.springframework.core.type.filter.AssignableTypeFilter
	 */筛选指定类型的bean
	ASSIGNABLE_TYPE,

	/**
	 * Filter candidates matching a given AspectJ type pattern expression.
	 * @see org.springframework.core.type.filter.AspectJTypeFilter
	 */ASPECTJ表达式
	ASPECTJ,

	/**
	 * Filter candidates matching a given regex pattern.
	 * @see org.springframework.core.type.filter.RegexPatternTypeFilter
	 */正则表达式
	REGEX,

	/** Filter candidates using a given custom
	 * {@link org.springframework.core.type.filter.TypeFilter} implementation.
	 */自定义类(给你扫描到的所有类,你选择哪些注入哪些不注入)
	CUSTOM
```


  扫描指定路径下的包,doScan方法
```
protected Set<BeanDefinitionHolder> doScan(String... basePackages) {
   Assert.notEmpty(basePackages, "At least one base package must be specified");
   Set<BeanDefinitionHolder> beanDefinitions = new LinkedHashSet<BeanDefinitionHolder>();
   for (String basePackage : basePackages) {
      Set<BeanDefinition> candidates = findCandidateComponents(basePackage);
      for (BeanDefinition candidate : candidates) {
         ScopeMetadata scopeMetadata = this.scopeMetadataResolver.resolveScopeMetadata(candidate);
         candidate.setScope(scopeMetadata.getScopeName());
         String beanName = this.beanNameGenerator.generateBeanName(candidate, this.registry);
         if (candidate instanceof AbstractBeanDefinition) {
            postProcessBeanDefinition((AbstractBeanDefinition) candidate, beanName);
         }
         if (candidate instanceof AnnotatedBeanDefinition) {
            AnnotationConfigUtils.processCommonDefinitionAnnotations((AnnotatedBeanDefinition) candidate);
         }
         if (checkCandidate(beanName, candidate)) {
            BeanDefinitionHolder definitionHolder = new BeanDefinitionHolder(candidate, beanName);
            definitionHolder = AnnotationConfigUtils.applyScopedProxyMode(scopeMetadata, definitionHolder, this.registry);
            beanDefinitions.add(definitionHolder);
            registerBeanDefinition(definitionHolder, this.registry);
         }
      }
   }
   return beanDefinitions;
}
```
查找符合条件的bean,findCandidateComponents方法
```
public Set<BeanDefinition> findCandidateComponents(String basePackage) {
		Set<BeanDefinition> candidates = new LinkedHashSet<BeanDefinition>();
		try {
			String packageSearchPath = ResourcePatternResolver.CLASSPATH_ALL_URL_PREFIX +
					resolveBasePackage(basePackage) + "/" + this.resourcePattern;
			Resource[] resources = this.resourcePatternResolver.getResources(packageSearchPath);
			boolean traceEnabled = logger.isTraceEnabled();
			boolean debugEnabled = logger.isDebugEnabled();
			for (Resource resource : resources) {
				if (traceEnabled) {
					logger.trace("Scanning " + resource);
				}
				if (resource.isReadable()) {
					try {
						MetadataReader metadataReader = this.metadataReaderFactory.getMetadataReader(resource);
						if (isCandidateComponent(metadataReader)) {
							ScannedGenericBeanDefinition sbd = new ScannedGenericBeanDefinition(metadataReader);
							sbd.setResource(resource);
							sbd.setSource(resource);
							if (isCandidateComponent(sbd)) {
								if (debugEnabled) {
									logger.debug("Identified candidate component class: " + resource);
								}
								candidates.add(sbd);
							}
							else {
								if (debugEnabled) {
									logger.debug("Ignored because not a concrete top-level class: " + resource);
								}
							}
						}
						else {
							if (traceEnabled) {
								logger.trace("Ignored because not matching any filter: " + resource);
							}
						}
					}
					catch (Throwable ex) {
						throw new BeanDefinitionStoreException(
								"Failed to read candidate component class: " + resource, ex);
					}
				}
				else {
					if (traceEnabled) {
						logger.trace("Ignored because not readable: " + resource);
					}
				}
			}
		}
		catch (IOException ex) {
			throw new BeanDefinitionStoreException("I/O failure during classpath scanning", ex);
		}
		return candidates;
	}
```

判断是否是合格的bean,下面的includeFilters和excludeFilters就是我们在注解中或者xml中自定义的类了

```
protected boolean isCandidateComponent(MetadataReader metadataReader) throws IOException {
   for (TypeFilter tf : this.excludeFilters) {
      if (tf.match(metadataReader, this.metadataReaderFactory)) {
         return false;
      }
   }
   for (TypeFilter tf : this.includeFilters) {
      if (tf.match(metadataReader, this.metadataReaderFactory)) {
         return isConditionMatch(metadataReader);
      }
   }
   return false;
}
```

自定义的IncludeFilter,返回true或者false

```
public class IncludeFilter implements TypeFilter {
    private String filterName="com.fcy.ComponentScan.Filter.IncludeFilter";
    public boolean match(MetadataReader metadataReader, MetadataReaderFactory metadataReaderFactory) throws IOException {
        ClassMetadata classMetadata = metadataReader.getClassMetadata();
        AnnotationMetadata annotationMetadata = metadataReader.getAnnotationMetadata();
        Resource resource = metadataReader.getResource();
        System.out.println("class:"+classMetadata.getClassName());
        System.out.println("annotation:"+annotationMetadata.getClassName());
        System.out.println("resource:"+resource.getFilename());
        return true;
    }
}
```





我们传递一个路径给spring

spring扫描这个路径得到下面的所有资源后再遍历了一遍,我们写的代码也就是可以对其过滤一下,选择哪些可以被注入,哪些不可以被注入

用简略的代码描述就是这样

```
File file=new File(path);
File[] files = file.listFiles();
Set<File> candidates=new HashSet();
for (File file1 : files) {
    if(customerFilter(file1)){
        candidates.add(file1);
    }
}
```

spring对其做了很多层抽象,目的在于应对可能存在的变化.如资源的类型有多种(普通文件,网络文件,jar文件,zip文件等)扫描文件的方式(前缀,后缀,正则等)

如下是一个某个调用路径会调用到的方法,这个是不是就是很熟悉的代码了呢

```
protected void doRetrieveMatchingFiles(String fullPattern, File dir, Set<File> result) throws IOException {
		if (logger.isDebugEnabled()) {
			logger.debug("Searching directory [" + dir.getAbsolutePath() +
					"] for files matching pattern [" + fullPattern + "]");
		}
		File[] dirContents = dir.listFiles();
		if (dirContents == null) {
			if (logger.isWarnEnabled()) {
				logger.warn("Could not retrieve contents of directory [" + dir.getAbsolutePath() + "]");
			}
			return;
		}
		for (File content : dirContents) {
			String currPath = StringUtils.replace(content.getAbsolutePath(), File.separator, "/");
			if (content.isDirectory() && getPathMatcher().matchStart(fullPattern, currPath + "/")) {
				if (!content.canRead()) {
					if (logger.isDebugEnabled()) {
						logger.debug("Skipping subdirectory [" + dir.getAbsolutePath() +
								"] because the application is not allowed to read the directory");
					}
				}
				else {
					doRetrieveMatchingFiles(fullPattern, content, result);
				}
			}
			if (getPathMatcher().match(fullPattern, currPath)) {
				result.add(content);
			}
		}
	}

```
