<?xml version="1.0"?>

<!-- This is the stylesheet that converts top-level XML output into HTML coverage reports.
	 The XSLT specification is at http://www.w3.org/TR/xslt/ -->

<xsl:stylesheet
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:import href="/webapp/WEB-INF/xslt/util-html.xslt"/>

<!-- Set the output method to HTML, which automatically handles some HTML tags
	 that do not conform to XML standards. -->
<xsl:output
	method="html"
	encoding="iso-8859-1"
	indent="yes"
	doctype-public="-//W3C//DTD HTML 4.01 Transitional//EN"/>


<!-- Spacing is not important in HTML, so this produces more compact output. -->
<xsl:strip-space elements="*"/>
<xsl:param name="session"/>

<xsl:template match="/">
	<html>
		<head>
			<title>QNX Code Coverage Report</title>
			<link rel="stylesheet" href="/qnx-coverage/report/report.css" /> 
		</head>
		<body>
			<xsl:apply-templates select="/coverage-progress"/>
			<xsl:apply-templates select="/coverage-report"/>
			<xsl:apply-templates select="/coverage-report/coverage-exception"/>
		</body>
	</html>
</xsl:template>

<xsl:template match="coverage-exception">
	<xsl:value-of select="message"/>
</xsl:template>
	
<xsl:template match="coverage-exception" mode="table-row">
	<tr><td colspan="3">
	<xsl:value-of select="message"/>
	</td>
	</tr>
</xsl:template>
	
<xsl:template match="coverage-progress">
	<xsl:variable name="percentage" select="format-number(percentage, '#')"/>
	<table border="0">
		<tr><td><br></br>Generating Report... (Please wait).</td></tr>
		<tr><td><xsl:value-of select="task"/></td></tr>
		<tr><td align="left">
			<div style="width:100px;height:16px;border:1px solid ThreeDShadow;">
				<div id="divProgress" style="width={$percentage}px;height:100%;background-color:black"></div>
			</div>
		</td></tr>
		<tr><td><xsl:value-of select="$percentage"/>% Complete</td></tr>
		<tr><td><xsl:value-of select="subtask"/></td></tr>
	</table>
	<script language="JavaScript">
	<xsl:text>function refresh() { window.location.reload(true) };</xsl:text>
	<xsl:text>setTimeout("refresh()", 500);</xsl:text>
	</script>
</xsl:template>	

<xsl:template match="coverage-report">
	<p class="report">Code Coverage Report</p>
	<p class="report">Report generated on: <xsl:value-of select="@time"/></p>
	<xsl:if test="@user">
		<p class="report">by user: <xsl:value-of select="@user"/></p>
	</xsl:if>
	<xsl:if test="@machine">
		<p class="report">from machine: <xsl:value-of select="@machine"/></p>
	</xsl:if>
	<br></br>
	<xsl:apply-templates select="sessions" mode="table"/>
	<xsl:apply-templates select="session" mode="heading"/>
	<xsl:apply-templates select="session/project" mode="table"/>
	<xsl:apply-templates select="session/projects" mode="table"/>
</xsl:template>
	
<xsl:template match="sessions" mode="table">
	<table class="report">
		<tr>
		<th class="session">Session</th><th class="when">When</th>
		</tr>
			<xsl:apply-templates select="session" mode="table-row"/>
	</table>
</xsl:template>

<xsl:template match="session" mode="table-row">
	<tr><td class="session">
		<a href="coverage?session={@id}"><xsl:value-of select="name"/></a>
	</td>
	<td>
		<xsl:value-of select="@time"/>
	</td></tr>
</xsl:template>

<xsl:template match="session" mode="heading">
	<p class="session"><b>Session name: </b><a href="coverage?session={@id}"><xsl:value-of select="name"/></a></p>
	<p class="session"><b>Time of session creation: </b><xsl:value-of select="@time"/></p>
	<p class="session"><b>Session identifier: </b><xsl:value-of select="@id"/></p>
	<xsl:if test="comment">
		<p class="session"><b>Comment: </b>
		<pre><xsl:value-of select="comment"/></pre></p>
	</xsl:if>
	<br></br>
</xsl:template>

<xsl:template match="projects" mode="table">
	<table class="report">
		<xsl:call-template name="project-table-heading"/>
		<xsl:apply-templates select="project" mode="table-row"/>
	</table>
</xsl:template>

<xsl:template match="project" mode="table">
	<table class="report">
		<xsl:call-template name="project-table-heading"/>
		<xsl:apply-templates select="." mode="table-row"/>
		<xsl:apply-templates select="folder" mode="table-row">
			<xsl:with-param name="project" select="@name"/>
			<xsl:with-param name="level" select="1"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="file" mode="table-row">
			<xsl:with-param name="level" select="1"/>
			<xsl:with-param name="project" select="@name"/>
			<xsl:sort select="coverage-data/code/percentage" data-type="number"/>
		</xsl:apply-templates>		
	</table>
</xsl:template>

<xsl:template name="project-table-heading">
	<tr>
		<th rowspan="3" class="coverage">Project/Folder/File/Function</th>
		<th colspan="6" class="coverage">Coverage</th>
	</tr>
	<tr>
		<th rowspan="2" colspan="2" class="sub-coverage">Total Code Coverage</th>
		<th colspan="4" class="sub-coverage">Source Line Coverage</th>
	</tr>
	<tr>
		<th class="sub-coverage">Lines Not Covered</th>
		<th class="sub-coverage">Lines Partially Covered</th>
		<th class="sub-coverage">Lines Fully Covered</th>
		<th class="sub-coverage">Total Lines</th>
	</tr>	
</xsl:template>

<xsl:template match="project" mode="table-row">
	<tr class="project">
		<td>
			<xsl:call-template name="coverage-url">
				<xsl:with-param name="path" select="@location"/>
				<xsl:with-param name="text" select="@name"/>
			</xsl:call-template>
		</td>		
		<xsl:apply-templates select="coverage-data">
			<xsl:with-param name="css_class" select="'project_num'"/>
		</xsl:apply-templates>		
	</tr>
</xsl:template>

<xsl:template match="folder" mode="table-row">
	<xsl:param name="project"/>
	<xsl:param name="level"/>
		<tr class="folder">
			<td>
			    <xsl:call-template name="indent">
			        <xsl:with-param name="level" select="$level"/>
			    </xsl:call-template>
				<xsl:call-template name="coverage-url">
					<xsl:with-param name="path" select="@location"/>
					<xsl:with-param name="text" select="@name"/>
				</xsl:call-template>
			</td>
			<xsl:apply-templates select="coverage-data">
				<xsl:with-param name="css_class" select="'folder_num'"/>
			</xsl:apply-templates>		
		</tr>
		<xsl:apply-templates select="file" mode="table-row">
			<xsl:with-param name="project" select="$project"/>
			<xsl:with-param name="path" select="@location"/>
			<xsl:with-param name="level" select="$level + 1"/>
			<xsl:sort select="coverage-data/code/percentage" data-type="number"/>
		</xsl:apply-templates>
	<xsl:apply-templates select="folder" mode="table-row">
		<xsl:with-param name="project" select="$project"/>
		<xsl:with-param name="level" select="$level + 1"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="file" mode="table-row">
	<xsl:param name="project"/>
	<xsl:param name="path"/>	
	<xsl:param name="level"/>
	<tr class="file">
		<td>
			<xsl:call-template name="indent">
				<xsl:with-param name="level" select="$level"/>
			</xsl:call-template>
			<xsl:call-template name="coverage-url">
				<xsl:with-param name="path" select="@location"/>
				<xsl:with-param name="text" select="@name"/>
			</xsl:call-template>
			<xsl:if test="count(source) = 0"> 
				&#160;&#160; 
				<xsl:call-template name="coverage-url">
					<xsl:with-param name="path" select="@location"/>
					<xsl:with-param name="options">&amp;source=1</xsl:with-param>
					<xsl:with-param name="text">(source)</xsl:with-param>
				 </xsl:call-template> 
			</xsl:if>
		</td>
		<xsl:apply-templates select="coverage-data">
			<xsl:with-param name="css_class" select="'file_num'"/>
		</xsl:apply-templates>
	</tr>
	
	<xsl:apply-templates select="functions" mode="table-row">
		<xsl:with-param name="project" select="$project"/>
		<xsl:with-param name="path" select="@location"/>
		<xsl:with-param name="filename" select="@name"/>
		<xsl:with-param name="level" select="$level"/>
	</xsl:apply-templates>
	
	<xsl:if test="function">
		<xsl:apply-templates select="function" mode="table-row">
			<xsl:with-param name="project" select="$project"/>
			<xsl:with-param name="path" select="concat($path,'/',@name)"/>
			<xsl:with-param name="filename" select="@name"/>
			<xsl:with-param name="level" select="$level + 1"/>
		</xsl:apply-templates>
	</xsl:if>
	<xsl:apply-templates select="source" mode="table-row"></xsl:apply-templates>
</xsl:template>

<xsl:template match="functions" mode="table-row">
	<xsl:param name="level"/>
	<xsl:param name="project"/>
	<xsl:param name="path"/>
	<xsl:param name="filename"/>
	<xsl:apply-templates select="function" mode="table-row">
		<xsl:with-param name="project" select="$project"/>
		<xsl:with-param name="path" select="$path"/>
		<xsl:with-param name="filename" select="$filename"/>
		<xsl:with-param name="level" select="$level + 1"/>
		<xsl:sort select="coverage-data/code/percentage" data-type="number"/>
	</xsl:apply-templates>
	<tr><th class="seperator" colspan="8"/></tr>
</xsl:template>

<xsl:template match="function" mode="table-row">
	<xsl:param name="level"/>
	<xsl:param name="project"/>
	<xsl:param name="path"/>
	<xsl:param name="filename"/>
	<tr class="function">
		<td>
		    <xsl:call-template name="indent">
		        <xsl:with-param name="level" select="$level"/>
	    	</xsl:call-template>
			<xsl:call-template name="coverage-url">
				<xsl:with-param name="path" select="$path"/>
				<xsl:with-param name="function" select="@name"/>
				<xsl:with-param name="text" select="@name"/>
			</xsl:call-template>
		</td>
		<xsl:apply-templates select="coverage-data">
			<xsl:with-param name="css_class" select="'function_num'"/>
		</xsl:apply-templates>		
	</tr>
	<xsl:apply-templates select="source" mode="table-row"></xsl:apply-templates>
</xsl:template>

<xsl:template match="source" mode="table-row">
	<tr>
		<td colspan="9">
		<table>
			<th class="slinecoverage">&#160;</th><th class="slineno">Line</th><th class="sline">Source Code</th>
			<xsl:apply-templates select="line"></xsl:apply-templates>
			<xsl:apply-templates select="coverage-exception" mode="table-row"/>
		</table>
		</td>
	</tr>
</xsl:template>

<xsl:template match="line">
	<tr>
	<xsl:choose >
		<xsl:when test="@covered = 0.0">
			<td class="slinecoverage"><img src="/qnx-coverage/report/not-executed-line.gif"></img></td>
			<td class="uslineno"><xsl:value-of select="@lineno"/></td>
			<td class="usline">
				<pre class="source"><xsl:value-of select="."/></pre>
			</td>
		</xsl:when>
		<xsl:when test="@covered = 1.0">
			<td class="slinecoverage"><img src="/qnx-coverage/report/all-executed-line.gif"></img></td>
			<td class="cslineno"><xsl:value-of select="@lineno"/></td>
			<td class="csline">
				<pre class="source"><xsl:value-of select="."/></pre>
			</td>
		</xsl:when>
		<xsl:when test="@covered > 0.0">
			<td class="slinecoverage"><img src="/qnx-coverage/report/part-executed-line.gif"></img></td>
			<td class="mslineno"><xsl:value-of select="@lineno"/></td>
			<td class="msline">
				<pre class="source"><xsl:value-of select="."/></pre>
			</td>
		</xsl:when>
		<xsl:otherwise>
			<td></td>
			<td class="slineno"><xsl:value-of select="@lineno"/></td>
			<td class="sline">
				<pre class="source"><xsl:value-of select="."/></pre>
			</td>
		</xsl:otherwise>
	</xsl:choose>
	</tr>
</xsl:template>
	
<xsl:template match="coverage-data">
	<xsl:param name="css_class"/>
	<xsl:variable name="bar-width">
	<xsl:choose>
		<xsl:when test="code/@percentage &lt;= 0 or code/@percentage > 0">
			<xsl:value-of select="code/@percentage"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="0"/>
		</xsl:otherwise>
	</xsl:choose>
	</xsl:variable>
	<td class="coverage_bar">
		<xsl:call-template name="bar">
			<xsl:with-param name="width" select="$bar-width" />
		</xsl:call-template>
	</td>
	<td class="{$css_class}">
		<xsl:choose>
			<xsl:when test="code/@percentage &lt;= 0 or code/@percentage > 0">
				<xsl:value-of select="format-number(code/@percentage, '0.00')"/>%
			</xsl:when>
			<xsl:otherwise>
				Unknown
			</xsl:otherwise>
		</xsl:choose>
	</td>
	<td class="{$css_class}">
		<xsl:value-of select="lines/@not-executed"/>
	</td>
	<td class="{$css_class}">
		<xsl:value-of select="lines/@partial-executed"/>
	</td>
	<td class="{$css_class}">
		<xsl:value-of select="lines/@fully-executed"/>
	</td>
	<td class="{$css_class}">
		<xsl:value-of select="lines/@total"/>
	</td>	
</xsl:template>

<xsl:template name="coverage-url">
	<xsl:param name="path"/>
	<xsl:param name="function"/>
	<xsl:param name="options"/>
	<xsl:param name="text"/>
	<a class="coverage-url">
		<xsl:attribute name="href">
			<xsl:text>coverage?session=</xsl:text>
			<xsl:call-template name="url-encode">
				<xsl:with-param name="str" select="$session"/>
			</xsl:call-template>
			<xsl:if test="string-length($path) > 0">
				<xsl:text>&amp;path=</xsl:text>
				<xsl:call-template name="url-encode">
					<xsl:with-param name="str" select="$path"/>
				</xsl:call-template>
			</xsl:if>
			<xsl:if test="string-length($function) > 0">
				<xsl:text>&amp;function=</xsl:text>
				<xsl:call-template name="url-encode">
					<xsl:with-param name="str" select="$function"/>
				</xsl:call-template>
			</xsl:if>
			<xsl:if test="string-length($options) > 0">
				<xsl:value-of select="$options"/>
			</xsl:if>
		</xsl:attribute>
		<xsl:value-of select="$text"/>
	</a>		
</xsl:template>

</xsl:stylesheet>
