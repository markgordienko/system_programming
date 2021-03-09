FROM alpine
COPY test.sh .
RUN chmod ugo+x test.sh
CMD ./test.sh