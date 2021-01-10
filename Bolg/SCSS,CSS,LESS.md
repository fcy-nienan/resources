Both [Sass](https://sass-lang.com/) and [Less](http://lesscss.org/) are CSS preprocessors.

From [keycdn.com](https://www.keycdn.com/blog/sass-vs-less/)

> A CSS preprocessor is basically a scripting language that extends CSS and then compiles it into regular CSS.

So Sass and Less don't change the functionality of CSS, as they are compiled into plain old CSS. What they do is make it easier to write and maintain CSS with tools such as mixins, nesting, variables, and more.

SCSS, which stands for 'Sassy CSS' is one of two syntaxes for Sass.
From the [sass reference](https://sass-lang.com/documentation/file.SASS_REFERENCE.html):

> The second and older syntax, known as the indented syntax (or sometimes just "Sass"), provides a more concise way of writing CSS.

### The difference

Both Sass and Less have very similar features. Sass uses Ruby whereas Less uses Javascript. There are syntactical differences, for example, Sass uses `$` for variables whereas less uses `@`.
There are some slightly more subjective differences, [this website](https://www.thebalancecareers.com/sass-vs-less-2071912) claims that "LESS Has More User-Friendly Documentation Than Sass", however personally I have found the Sass documentation and examples very easy to use.



##

SCSS和LESS都是CSS的预处理器

CSS没有嵌套,不能重用

CSS预处理器增加了,变量,混入,继承,嵌套等

> > https://tw.alphacamp.co/blog/css-preprocessor-sass-scss
> >
> > https://www.lambdatest.com/blog/css-preprocessors-sass-vs-less-vs-stylus-with-examples/

Variable definitions right:

```
$      => SCSS, SASS
--     => CSS
@      => LESS
```