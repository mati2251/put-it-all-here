# syntax=docker/dockerfile:1.3-labs
FROM ubuntu

RUN <<EOF
	apt update
	apt install -y bind9 dnsutils iproute2 iputils-ping
EOF


COPY config-files /etc/bind/

CMD service named restart && tail -F /var/log/lastlog
