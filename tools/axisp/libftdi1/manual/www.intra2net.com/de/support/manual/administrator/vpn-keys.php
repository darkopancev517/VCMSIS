<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Schl&uuml;sselmanagement | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn.php" title="Teil&nbsp;6.&nbsp;VPN"><link rel="prev" href="vpn-basics-compatibility.php" title="38.7. Kompatibilit&auml;t mit anderen IPSec-Gegenstellen"><link rel="next" href="vpn-keys-foreign.php" title="39.2. Fremde Schl&uuml;ssel">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="vpn-keys.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-keys.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">39. Kapitel - Schl&uuml;sselmanagement</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-basics-compatibility.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;6.&nbsp;VPN</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-keys-foreign.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="vpn-keys"></a>39. Kapitel - Schl&uuml;sselmanagement</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="vpn-keys.php#vpn-keys-own">39.1. Eigene Schl&uuml;ssel</a></span></dt><dd><dl><dt><span class="sect2"><a href="vpn-keys.php#vpn-keys-own-ca">39.1.1. Zertifizierungsstellen (CAs)</a></span></dt></dl></dd><dt><span class="sect1"><a href="vpn-keys-foreign.php">39.2. Fremde Schl&uuml;ssel</a></span></dt></dl></div><a class="indexterm" name="vpn-keys1"></a><a class="indexterm" name="vpn-keys2"></a><a class="indexterm" name="vpn-keys3"></a><p>F&uuml;r Public-Key Verschl&uuml;sselungsverfahren m&uuml;ssen vor dem Verbindungsaufbau auf jeder Seite
    geheime Schl&uuml;ssel erzeugt und die dazugeh&ouml;rigen &ouml;ffentlichen Schl&uuml;ssel mit der Gegenstelle
    ausgetauscht werden.</p><p>Hierzu ist im Intranator eine Schl&uuml;sselverwaltung vorgesehen.</p><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-keys-own"></a>39.1. Eigene Schl&uuml;ssel</h2></div></div></div><p>Im Men&uuml; <span class="command"><strong>System &gt; Schl&uuml;ssel &gt; Eigene Schl&uuml;ssel</strong></span> k&ouml;nnen
      eigene Schl&uuml;sselpaare aus Public- und Private-Key erzeugt werden.</p><p>Die Schl&uuml;ssel werden nach dem X.509-Standard erstellt. Die meisten IPSec-Implementierungen
      beherrschen diesen Schl&uuml;sseltyp. Er hat einen etwas komplexeren Aufbau und kommt au&szlig;er f&uuml;r
      IPSec auch f&uuml;r SSL/TLS (z.B. bei HTTPS) und zur Verschl&uuml;sselung von E-Mails (S/MIME) zum
      Einsatz.</p><p>Die Sicherheit der Verschl&uuml;sselung h&auml;ngt unter anderem von der Schl&uuml;ssell&auml;nge in Bit ab.
      Der Intranator unterst&uuml;tzt Schl&uuml;ssell&auml;ngen von 512 bis 4096 Bit. Je l&auml;nger der Schl&uuml;ssel,
      desto sicherer ist die Verbindung. Einige Gegenstellen unterst&uuml;tzen nicht alle Schl&uuml;ssell&auml;ngen
      oder werden durch zu lange Schl&uuml;ssel &uuml;berlastet. Wir empfehlen die Verwendung von 2048
      Bit.</p><p>Als Inhaberdaten k&ouml;nnen bei X.509 Schl&uuml;sseln Landesk&uuml;rzel (2-stellig), Bundesland, Stadt,
      Firmenname, Abteilungsname, Rechnername und E-Mail-Adresse angegeben werden. Es muss dabei
      entweder ein Rechnername oder eine E-Mail-Adresse angegeben sein, der Rest der Daten ist
      freiwillig.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Die Inhaberdaten eines Schl&uuml;ssels m&uuml;ssen unbedingt eindeutig sein. Die Inhaberdaten
        eines Schl&uuml;ssels d&uuml;rfen also auf diesem und allen per VPN verbundenen Ger&auml;ten nur einmal
        vorkommen.</p></td></tr></table></div><p>Aus Sicherheitsgr&uuml;nden ist die G&uuml;ltigkeitsdauer eines X.509-Schl&uuml;ssels beschr&auml;nkt. Nach
      dem Ablauf der G&uuml;ltigkeitsdauer wird der Schl&uuml;ssel nicht mehr akzeptiert und muss erneuert
      werden. Eine Verl&auml;ngerung der G&uuml;ltigkeit ist nicht m&ouml;glich.</p><p>Um den Public-Key an die Gegenstelle zu &uuml;bermitteln, kann er mit <span class="command"><strong>Zertifikat
        exportieren</strong></span> in eine Datei gespeichert werden.</p><p>Wenn Sie auf dem Intranator mehrere VPNs einrichten, m&uuml;ssen Sie nicht f&uuml;r jede Verbindung
      extra einen eigenen Schl&uuml;ssel anlegen: Sie k&ouml;nnen einen eigenen Schl&uuml;ssel f&uuml;r alle VPNs
      verwenden. Nur von jeder der Gegenstellen ben&ouml;tigen Sie nat&uuml;rlich den &ouml;ffentlichen
      Schl&uuml;ssel.</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="vpn-keys-own-ca"></a>39.1.1. Zertifizierungsstellen (CAs)</h3></div></div></div><a class="indexterm" name="vpn-keys-own-ca1"></a><a class="indexterm" name="vpn-keys-own-ca2"></a><p>Um die Bedienung zu vereinfachen, erzeugt der Intranator normalerweise selbstsignierte
        Zertifikate, bei denen der Inhaber (Subject genannt) auch gleichzeitig der
        Zertifikatsaussteller (Issuer) ist.</p><p>Wenn Sie stattdessen eine CA verwenden wollen, so erzeugen Sie zuerst einen normalen
        Schl&uuml;ssel. Unter dem Reiter CA k&ouml;nnen Sie eine Zertifikatsanforderung exportieren. Diese
        Zertifikatsanforderung wird von der CA signiert und kann dann als Zertifikat wieder in den
        Intranator importiert werden.</p><p>Einige VPN-Gegenstellen akzeptieren keine selbstsignierten Schl&uuml;ssel, sondern fordern
        Schl&uuml;ssel, die von einer CA signiert wurden. Um Kompatibilit&auml;t mit solchen Gegenstellen
        einfach herzustellen, gibt es die Option <span class="guimenuitem">Schl&uuml;ssel mit einem anderen Schl&uuml;ssel
          signieren</span>.</p><p>Wenn Sie es mit einer solchen Gegenstelle zu tun haben, gehen Sie wie folgt vor: </p><div class="orderedlist"><ol type="1"><li><p>Legen Sie einen neuen eigenen Schl&uuml;ssel vom Typ X.509 an. Dieses Zertifikat wird nur
            indirekt zum Signieren verwendet, nennen Sie es deshalb beispielsweise
              <strong class="userinput"><code>intranator-ca</code></strong>.</p></li><li><p>Exportieren Sie dieses Zertifikat und importieren es auf der Gegenseite als
            vertrauensw&uuml;rdige Root-CA.</p></li><li><p>Legen Sie nun auf dem Intranator einen weiteren eigenen Schl&uuml;ssel an. Dieser wird
            nachher vom Intranator f&uuml;r das VPN genutzt.</p></li><li><p>Verwenden Sie die Option <span class="guimenuitem">Schl&uuml;ssel mit einem anderen Schl&uuml;ssel
              signieren</span> um diesen Schl&uuml;ssel mit dem vorher erstellen CA-Schl&uuml;ssel zu
            signieren.</p></li></ol></div><a class="indexterm" name="d0e12053"></a><a class="indexterm" name="d0e12054"></a></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-basics-compatibility.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-keys-foreign.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">38.7. Kompatibilit&auml;t mit anderen IPSec-Gegenstellen&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;39.2. Fremde Schl&uuml;ssel</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>