# Get docker image(alpine linux) --- layer 1
FROM alpine:latest
# Set working directory(/usr/src/app). This dir is used by Flask --- layer 2
WORKDIR /usr/src/app

# Run terminal command --- layer 3(execute all commands once in a layer. If not, it takes a lot of time)
# wget {url} : install files for running Flask server(1 file needed)
# apk add {package} : install packages(python3, pip needed)
# pip3 install flask : install Flask
RUN wget https://raw.githubusercontent.com/ghkdxofla/cloudComputing/master/material/assignment_3/app.py \
&& apk update \
&& apk add python3 \
&& apk add py-pip \
&& pip3 install flask

# Open 8080 port
EXPOSE 8080
# Run Flask server after configuration(if not, docker is closed immediately)
CMD ["python3", "app.py"]