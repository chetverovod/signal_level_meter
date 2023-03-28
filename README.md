# signal_level_meter
Simple audio signal level meter based on Mediastreamer2.

This program is example of simple audio signal level meter for my article on Medium:<br>
[What’s Mediastreamer2. Examples of Filters Using](https://medium.com/gitconnected/chapter-3-examples-of-using-filters-612f2121301)

Russian version in book (page 20):<br>["Изучаем Mediastreamer2"](https://drive.google.com/file/d/1OEY1VwcelQXMg3oF0HFuolZ11dlFv1lO/view?usp=sharing) 

Scheme of generator<br>
![image](https://user-images.githubusercontent.com/1526432/228359749-4c5e569d-d05f-45db-9dff-156661b5ab4b.png)

## How to compile

```
$ gcc mstest3.c -o mstest3 `pkg-config mediastreamer --libs --cflags`
```
## How to run

```
$ ./mstest3
```
You will see prints of measurement signal.
