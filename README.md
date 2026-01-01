Our target is get a output image and display it, after get a rayTracing we need to trans it into a ppm file.
./rayTracing > image.ppm

```
file image.ppm
image.ppm: Netpbm image data, size = 200 x 100, pixmap, ASCII text
```
```
head image.ppm
P3
200 100
255
```
only this kind of file can display it.

```
display image.ppm
```

We can use ./run.sh to test the result.
