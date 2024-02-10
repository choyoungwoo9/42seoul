/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Structrue.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:33:40 by hocsong           #+#    #+#             */
/*   Updated: 2023/07/03 14:17:26 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
#include <vector>
#include <string>
// # include "includeAll.hpp"
/*
	Configuration 구조체.
*/

typedef struct sLocationConfig
{
	std::vector<int>	acceptableMethods; // 빈 경우 모든 method(이 과제에서는 GET POST DELETE)가 acceptable.
	std::string			redirection; // 빈 경우 리디렉트를 하지않는다.
	std::string			rootDirectory; // 실행부에서 자원 URL에 rootDirectory를 prepend한다.
	int					shouldListDirectory; // 파일 탐색기와 같이 디렉토리를 나열할지 정하는 플래그.
	std::string			defaultFile; // 요청 URL이 directory일 경우 서버에서 클라이언트로 보낼 파일.
	int					shouldAcceptFile; // 파일 업로드를 받을지 정하는 플래그.
	std::string			cgiExtension; // 어떤 확장자를 갖는 주소를 cgi로 판단할지 정한다. 빈 경우 어떠한 파일도 cgi로 판단하지 않음.
}tLocationConfig;

typedef struct sServerConfig
{
	short							port;
	std::string						hostAddr;
	std::string						serverName; // 빈 경우 서버 선택에 영향을 주지 않음.
	std::string						errorPages; // 빈 경우 nginx가 어떤 페이지를 보여주는지는 아직 모름.
	unsigned long long				bodySizeLimit; // 설정이 없는 경우 1MB
	std::vector<tLocationConfig>	locationConfig;
	int								isConfigEmpty;
}tServerConfig;

typedef struct sReqMsg
{
	int			method;
	std::string	requestTarget;
	float		protocolVersion;
	std::string	host;
	long		contentLen;
	std::string	accept;
	std::string	acceptEncoding;
	std::string	acceptLanguage;
	std::string	contentType;
	std::string	connection;
	std::string	cookie;
	std::string	transferEncoding;
	std::string	body;
}tReqMsg;

typedef struct sResponseMsg
{
	float		protocolVersion;
	int			code;
	std::string	location;
	std::string	allow;
	long long	contentLen;
	std::string	contentType;
	std::string	date;
	std::string	transferEncoding;
	std::string	server;
	std::string body;
}tResponseMsg;

#endif