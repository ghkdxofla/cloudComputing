# Get docker image(alpine linux) --- layer 1
FROM alpine:latest
# Set working directory(/usr/src/app). This dir is used by node.js --- layer 2
WORKDIR /usr/src/app

# Run terminal command --- layer 3(execute all commands once in a layer. If not, it takes a lot of time)
# wget {url} : install files for running node.js server(3 files needed)
# apk add {package} : install packages(node.js and npm)
# npm install : install node.js packages(package.json and package-lock.json is included package lists)
RUN wget https://raw.githubusercontent.com/KU-Cloud/hello-docker/master/index.js \
&& wget https://raw.githubusercontent.com/KU-Cloud/hello-docker/master/package-lock.json \
&& wget https://raw.githubusercontent.com/KU-Cloud/hello-docker/master/package.json \
&& apk add nodejs \
&& apk add npm \
&& npm install

# Open 8080 port
EXPOSE 8080
# Run node.js server after configuration(if not, docker is closed immediately)
CMD ["npm", "start"]