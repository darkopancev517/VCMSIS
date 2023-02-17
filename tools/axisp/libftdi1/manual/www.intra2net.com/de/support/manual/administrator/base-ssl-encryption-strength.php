<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Verschl&uuml;sselungsst&auml;rke | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-ssl-encryption.php" title="10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate"><link rel="prev" href="base-ssl-encryption-ca.php" title="10.5. Verwenden einer externen Zertifizierungsstelle"><link rel="next" href="base-internet.php" title="11. Kapitel - Internet">
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

<a href="base-ssl-encryption-strength.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-ssl-encryption-strength.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">10.6. Verschl&uuml;sselungsst&auml;rke</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-ssl-encryption-ca.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">10. Kapitel - SSL-Verschl&uuml;sselung und Zertifikate</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-internet.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-ssl-encryption-strength"></a>10.6. Verschl&uuml;sselungsst&auml;rke</h2></div></div></div><a class="indexterm" name="base-ssl-encryption-strength1"></a><a class="indexterm" name="base-ssl-encryption-strength2"></a><a class="indexterm" name="base-ssl-encryption-strength3"></a><p>Die Kryptographie und die Leistungsf&auml;higkeit von CPUs entwickelte sich in den letzten
      Jahren schnell weiter. Bisher als sicher geltende Verschl&uuml;sselungsverfahren sind mittlerweile
      als geknackt anzusehen und sollten daher nicht mehr eingesetzt werden. Gleichzeitig gibt es
      aber auch noch &auml;ltere Systeme, die mit neueren Verfahren noch nicht umgehen k&ouml;nnen.</p><p>Der Intranator erlaubt daher eine gezielte Steuerung der angebotenen
      Verschl&uuml;sselungsverfahren, getrennt nach Verbindungen im lokalen Netz und Internet. Diese ist
      zu finden im Men&uuml;
        <span class="guimenu">System&nbsp;&gt;&nbsp;Weboberfl&auml;che&nbsp;&gt;&nbsp;Sicherheit</span>.
      Die dort gew&auml;hlten Einstellungen gelten f&uuml;r die mit SSL bzw. TLS gesicherten Verbindungen bei
      folgenden Protokollen bzw. Diensten: Die Weboberfl&auml;che und Webgroupware, ActiveSync, POP3(S),
      IMAP(S) und SMTP-Submission.</p><p>F&uuml;r jeden der beiden Bereiche gibt es dabei folgende Optionen:</p><div class="informaltable"><table border="1"><colgroup><col align="left"><col align="left"></colgroup><tbody><tr><td align="left">Schwach</td><td align="left">Erlaubt Verbindungen mit schwachen und als geknackt geltenden
              Verschl&uuml;sselungsverfahren wie z.B. RC4. Diese Einstellung ist ein Sicherheitsrisiko
              und sollte nur ausnahmsweise aktiviert werden.</td></tr><tr><td align="left">Windows XP kompatibel</td><td align="left">Erlaubt schw&auml;chere Verschl&uuml;sselung und Schl&uuml;ssel-Austauschverfahren, um
              Kompatibilit&auml;t mit &auml;lteren Betriebssystemen wie z.B. Windows XP herzustellen. Diese
              Einstellung schaltet jedoch das als geknackt geltende RC4-Verfahren ab. Mit neueren
              Systemen die diese unterst&uuml;tzen, werden automatisch st&auml;rkere Verfahren, inkl. PFS,
              ausgehandelt.</td></tr><tr><td align="left">Stark (nur PFS)</td><td align="left">Erzwingt PFS f&uuml;r alle Verbindungen. Zus&auml;tzlich werden alle Verbindungen nur mit
              dem AES Verfahren verschl&uuml;sselt. Dies ist die empfohlene Einstellung f&uuml;r alle
              Verbindungen.</td></tr></tbody></table></div><p><b><span class="foreignphrase"><em class="foreignphrase">Perfect Forward Secrecy</em></span> (<abbr class="abbrev">PFS</abbr>).&nbsp;</b>bewirkt, dass die &uuml;bermittelten Daten auch dann nicht entschl&uuml;sselt werden k&ouml;nnen, wenn
        zu einem sp&auml;teren Zeitpunkt der private Schl&uuml;ssel des Intranators bekannt werden sollte und
        eine fr&uuml;her aufgezeichnete &Uuml;bertragung dann mit Kenntnis des privaten Schl&uuml;ssels analysiert
        wird.</p><p>Der private Schl&uuml;ssel kann z.B. durch einen erfolgreichen Angriff auf den Intranator,
      durch Diebstahl des gesamten Ger&auml;ts oder staatliche Ma&szlig;nahmen in die falschen H&auml;nde geraten.
      In diesem Moment k&ouml;nnten ohne PFS alle fr&uuml;heren Verbindungen, sofern sie jemand aufgezeichnet
      haben sollte, entschl&uuml;sselt werden.</p><p>PFS handelt beim Verbindungsaufbau einen nur f&uuml;r diese Verbindung geltenden, tempor&auml;ren
      Schl&uuml;ssel aus ohne diesen dabei &uuml;ber die Leitung zu &uuml;bertragen. Dieser wird nach Ende der
      Verbindung gel&ouml;scht und kann daher zu einem sp&auml;teren Zeitpunkt nicht mehr rekonstruiert und
      mi&szlig;braucht werden.</p><a class="indexterm" name="d0e2213"></a><a class="indexterm" name="d0e2214"></a><a class="indexterm" name="d0e2215"></a></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-ssl-encryption-ca.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-ssl-encryption.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-internet.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">10.5. Verwenden einer externen Zertifizierungsstelle&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;11. Kapitel - Internet</td></tr></table></div>
      
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