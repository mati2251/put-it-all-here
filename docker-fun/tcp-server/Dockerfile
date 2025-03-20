# Base image
FROM ubuntu
# working directory
WORKDIR /work
# Copy contents
COPY ./files /work
# Add is similar to copy but works with url too 
ADD https://raw.githubusercontent.com/mati2251/docker-fun/main/data-persistence/bind-mounts/remove.sh /work
# Run commands
RUN apt update && apt install -y netcat iproute2
RUN echo *
# Expose port
EXPOSE 80
# Set env
ENV ENV_1 Wow
# Default command start after run image (alternative you can use entrypoint
CMD netcat -l -p 80
