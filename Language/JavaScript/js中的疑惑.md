# how to import npm module in html
Package installed by npm is located in /node_modules/ which cannot be used by front end directly. To use those modules, you need to use ES6 syntax and import them by using the following code:

// Just an example, you need to read the doc to see how to import
import html2cavas from "html2cavas"
However, browser cannot read ES6 syntax directly. As a result, you need to use Babel to transpile your ES6 code to normal JS code. See https://hackernoon.com/use-es6-javascript-syntax-require-import-etc-in-your-front-end-project-5eefcef745c2

After you transpiled your code, use the <script> tag to import the transpiled code.

Alternatively, you might be able to copy what you need from /node_modules/ and copy it to your js folder. However it is not recommended.